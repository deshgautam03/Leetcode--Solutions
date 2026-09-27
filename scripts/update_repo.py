"""
Two jobs in one pass:

1. Moves each problem folder under solutions/ into an Easy/Medium/Hard
   subfolder, based on LeetCode's public problem list (matched by the
   numeric ID prefix in the folder name, e.g. "0167" in
   "0167-two-sum-ii---input-array-is-sorted").

2. Regenerates a "Solved Problems" table inside README.md, between two
   HTML comment markers, listing every problem currently under solutions/
   with its real LeetCode title, difficulty, and links to both the
   original problem and your solution folder.

Safe to run repeatedly. No LeetCode login required — everything here uses
LeetCode's public problem list.
"""

import re
from pathlib import Path
import shutil

import requests

SOLUTIONS_DIR = Path("solutions")
README_PATH = Path("README.md")
DIFFICULTY_FOLDERS = {"Easy", "Medium", "Hard"}
ALL_PROBLEMS_URL = "https://leetcode.com/api/problems/all/"

FOLDER_NAME_RE = re.compile(r"^(\d+)-")
LEVEL_TO_DIFFICULTY = {1: "Easy", 2: "Medium", 3: "Hard"}
DIFFICULTY_EMOJI = {"Easy": "🟢", "Medium": "🟡", "Hard": "🔴"}

TABLE_START_MARKER = "<!-- LEETCODE-SOLUTIONS:START -->"
TABLE_END_MARKER = "<!-- LEETCODE-SOLUTIONS:END -->"

HEADERS = {"User-Agent": "Mozilla/5.0 (leetcode-sync-bot)"}


def fetch_problem_data() -> dict:
    """Returns {frontend_id (int): {'title': str, 'slug': str, 'difficulty': str}}"""
    resp = requests.get(ALL_PROBLEMS_URL, headers=HEADERS, timeout=30)
    resp.raise_for_status()
    data = resp.json()

    mapping = {}
    for item in data.get("stat_status_pairs", []):
        stat = item.get("stat", {})
        frontend_id = stat.get("frontend_question_id")
        level = item.get("difficulty", {}).get("level")
        if frontend_id is None or level not in LEVEL_TO_DIFFICULTY:
            continue
        mapping[int(frontend_id)] = {
            "title": stat.get("question__title", "Unknown"),
            "slug": stat.get("question__title_slug", ""),
            "difficulty": LEVEL_TO_DIFFICULTY[level],
        }
    return mapping


def sort_folders(problem_data: dict) -> None:
    if not SOLUTIONS_DIR.exists():
        print("No solutions/ folder found, skipping sort step.")
        return

    moved_count = 0
    for entry in sorted(SOLUTIONS_DIR.iterdir()):
        if not entry.is_dir() or entry.name in DIFFICULTY_FOLDERS:
            continue

        match = FOLDER_NAME_RE.match(entry.name)
        if not match:
            print(f"Skipping '{entry.name}' (doesn't start with '<number>-')")
            continue

        frontend_id = int(match.group(1))
        info = problem_data.get(frontend_id)
        if not info:
            print(f"Skipping '{entry.name}' (problem #{frontend_id} not found)")
            continue

        destination_folder = SOLUTIONS_DIR / info["difficulty"]
        destination_folder.mkdir(exist_ok=True)
        destination = destination_folder / entry.name

        if destination.exists():
            print(f"'{destination}' already exists, skipping move for '{entry.name}'")
            continue

        shutil.move(str(entry), str(destination))
        print(f"Moved '{entry.name}' -> {info['difficulty']}/")
        moved_count += 1

    print(f"Sort step done. Moved {moved_count} folder(s).\n")


def build_solved_table(problem_data: dict) -> str:
    rows = []

    for difficulty in ("Easy", "Medium", "Hard"):
        folder = SOLUTIONS_DIR / difficulty
        if not folder.exists():
            continue

        for entry in sorted(folder.iterdir()):
            if not entry.is_dir():
                continue
            match = FOLDER_NAME_RE.match(entry.name)
            if not match:
                continue

            frontend_id = int(match.group(1))
            info = problem_data.get(frontend_id)
            title = info["title"] if info else entry.name
            slug = info["slug"] if info else ""

            problem_link = f"https://leetcode.com/problems/{slug}/" if slug else ""
            solution_link = f"{SOLUTIONS_DIR}/{difficulty}/{entry.name}"

            title_cell = f"[{title}]({problem_link})" if problem_link else title
            rows.append(
                (frontend_id, f"| {frontend_id} | {title_cell} | "
                              f"{DIFFICULTY_EMOJI[difficulty]} {difficulty} | "
                              f"[Solution]({solution_link}) |")
            )

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
    problem_data = fetch_problem_data()
    print(f"Loaded data for {len(problem_data)} problems.\n")

    sort_folders(problem_data)

    table_markdown = build_solved_table(problem_data)
    update_readme(table_markdown)


if __name__ == "__main__":
    main()
