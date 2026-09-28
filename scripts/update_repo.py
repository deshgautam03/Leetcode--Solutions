"""
Two jobs in one pass:

1. Sorts every problem folder under solutions/ (whether currently loose at
   the top level, or already inside Easy/Medium/Hard) into the CORRECT
   Easy/Medium/Hard subfolder, matched by problem SLUG rather than by the
   number in the folder name. joshcai/leetcode-sync's folder-name number is
   not LeetCode's public problem number, so it can't be trusted for lookups
   -- but the slug (the text after the number) reliably maps to LeetCode's
   real problem data once hyphen-run artifacts are normalized away (e.g. a
   title containing " - " gets folder-encoded as "---").

2. Regenerates a "Solved Problems" table inside README.md, between two
   HTML comment markers, using LeetCode's real titles and problem numbers.

Safe to run repeatedly, and will correct any previously mis-sorted folders.
No LeetCode login required -- everything here uses LeetCode's public
problem list.
"""

import re
from pathlib import Path
import shutil

import requests

SOLUTIONS_DIR = Path("solutions")
README_PATH = Path("README.md")
DIFFICULTY_FOLDERS = ("Easy", "Medium", "Hard")
ALL_PROBLEMS_URL = "https://leetcode.com/api/problems/all/"

FOLDER_NAME_RE = re.compile(r"^(\d+)-(.+)$")
LEVEL_TO_DIFFICULTY = {1: "Easy", 2: "Medium", 3: "Hard"}
DIFFICULTY_EMOJI = {"Easy": "🟢", "Medium": "🟡", "Hard": "🔴"}

TABLE_START_MARKER = "<!-- LEETCODE-SOLUTIONS:START -->"
TABLE_END_MARKER = "<!-- LEETCODE-SOLUTIONS:END -->"

HEADERS = {"User-Agent": "Mozilla/5.0 (leetcode-sync-bot)"}


def normalize_slug(raw: str) -> str:
    """Collapses hyphen runs (from folder-encoded punctuation like ' - ') and trims edges."""
    return re.sub(r"-{2,}", "-", raw).strip("-").lower()


def fetch_problem_data() -> dict:
    """Returns {slug: {'frontend_id': int, 'title': str, 'slug': str, 'difficulty': str}}"""
    resp = requests.get(ALL_PROBLEMS_URL, headers=HEADERS, timeout=30)
    resp.raise_for_status()
    data = resp.json()

    by_slug = {}
    for item in data.get("stat_status_pairs", []):
        stat = item.get("stat", {})
        slug = stat.get("question__title_slug")
        level = item.get("difficulty", {}).get("level")
        frontend_id = stat.get("frontend_question_id")
        if not slug or level not in LEVEL_TO_DIFFICULTY or frontend_id is None:
            continue
        by_slug[slug] = {
            "frontend_id": int(frontend_id),
            "title": stat.get("question__title", "Unknown"),
            "slug": slug,
            "difficulty": LEVEL_TO_DIFFICULTY[level],
        }
    return by_slug


def find_problem_folders():
    """Yields (current_path, folder_name) for every problem folder, wherever it currently sits."""
    if not SOLUTIONS_DIR.exists():
        return

    for entry in sorted(SOLUTIONS_DIR.iterdir()):
        if not entry.is_dir():
            continue
        if entry.name in DIFFICULTY_FOLDERS:
            # Look one level inside each difficulty folder.
            for inner in sorted(entry.iterdir()):
                if inner.is_dir():
                    yield inner
        else:
            yield entry


def sort_folders(problem_by_slug: dict) -> dict:
    """Moves folders to the correct difficulty subfolder. Returns {folder_name: info} for the table step."""
    resolved = {}
    moved_count = 0
    unresolved_count = 0

    for entry in list(find_problem_folders()):
        match = FOLDER_NAME_RE.match(entry.name)
        if not match:
            print(f"Skipping '{entry.name}' (doesn't match '<number>-<slug>' pattern)")
            continue

        slug_guess = normalize_slug(match.group(2))
        info = problem_by_slug.get(slug_guess)

        if not info:
            print(f"Could not resolve difficulty for '{entry.name}' (slug guess: '{slug_guess}')")
            unresolved_count += 1
            continue

        resolved[entry.name] = info
        target_folder = SOLUTIONS_DIR / info["difficulty"]
        target_path = target_folder / entry.name

        if entry.resolve() == target_path.resolve():
            continue  # already in the right place

        target_folder.mkdir(exist_ok=True)

        if target_path.exists():
            # A resubmission recreated this folder at its original (pre-sort) path.
            # Treat the freshly-synced copy as authoritative and replace the old one.
            print(f"'{target_path}' already exists — replacing with resubmitted copy of '{entry.name}'")
            shutil.rmtree(target_path)

        shutil.move(str(entry), str(target_path))
        print(f"Moved '{entry.name}' -> {info['difficulty']}/")
        moved_count += 1

    print(f"\nSort step done. Moved/corrected {moved_count} folder(s), "
          f"{unresolved_count} unresolved.\n")
    return resolved


def build_solved_table(resolved: dict) -> str:
    rows = []

    for folder_name, info in resolved.items():
        difficulty = info["difficulty"]
        solution_link = f"{SOLUTIONS_DIR}/{difficulty}/{folder_name}"
        problem_link = f"https://leetcode.com/problems/{info['slug']}/"
        title_cell = f"[{info['title']}]({problem_link})"

        rows.append((
            info["frontend_id"],
            f"| {info['frontend_id']} | {title_cell} | "
            f"{DIFFICULTY_EMOJI[difficulty]} {difficulty} | "
            f"[Solution]({solution_link}) |",
        ))

    rows.sort(key=lambda r: r[0])

    lines = [
        "| # | Problem | Difficulty | Solution |",
        "|---|---------|------------|----------|",
    ]
    lines.extend(row_text for _, row_text in rows)
    lines.append(f"\n_Total solved: {len(rows)}_")

    return "\n".join(lines)


def update_readme(table_markdown: str) -> None:
    if not README_PATH.exists():
        print("No README.md found, creating a minimal one.")
        README_PATH.write_text(
            f"# LeetCode Solutions\n\n## ✅ Solved Problems\n\n"
            f"{TABLE_START_MARKER}\n{table_markdown}\n{TABLE_END_MARKER}\n"
        )
        return

    content = README_PATH.read_text()

    if TABLE_START_MARKER in content and TABLE_END_MARKER in content:
        pattern = re.compile(
            re.escape(TABLE_START_MARKER) + r".*?" + re.escape(TABLE_END_MARKER),
            re.DOTALL,
        )
        new_block = f"{TABLE_START_MARKER}\n{table_markdown}\n{TABLE_END_MARKER}"
        content = pattern.sub(new_block, content)
    else:
        content = (
            content.rstrip()
            + f"\n\n## ✅ Solved Problems\n\n"
            + f"{TABLE_START_MARKER}\n{table_markdown}\n{TABLE_END_MARKER}\n"
        )

    README_PATH.write_text(content)
    print("README.md updated.")


def main() -> None:
    print("Fetching full LeetCode problem list...")
    problem_by_slug = fetch_problem_data()
    print(f"Loaded data for {len(problem_by_slug)} problems.\n")

    resolved = sort_folders(problem_by_slug)

    table_markdown = build_solved_table(resolved)
    update_readme(table_markdown)


if __name__ == "__main__":
    main()
