#!/bin/bash

clear

TODO_FILE="${1:-TODO.md}"

echo -e "Current Progress:\n"
git diff --stat

echo ""

if [ ! -f "$TODO_FILE" ]; then
echo "Could not find todo file: $TODO_FILE"
echo ""
echo "Usage:"
echo "  ./tools/progress.sh"
echo "  ./tools/progress.sh README.md"
echo "  ./tools/progress.sh TODO.md"
exit 1
fi

echo "TODO File: $TODO_FILE"
echo ""

total_item_count=$(grep -E '^[[:space:]]*- \[[ xX]\]' "$TODO_FILE" | wc -l)
done_item_count=$(grep -E '^[[:space:]]*- \[[xX]\]' "$TODO_FILE" | wc -l)
open_item_count=$(grep -E '^[[:space:]]*- \[ \]' "$TODO_FILE" | wc -l)

if [ "$total_item_count" -eq 0 ]; then
progress_percent=0
else
progress_percent=$((100 * done_item_count / total_item_count))
fi

echo ""
echo "Project Progress:"
echo "  Total Items: $total_item_count"
echo "  Done:        $done_item_count"
echo "  Open:        $open_item_count"
echo "  Progress:    $progress_percent%"

echo ""
echo "Source TODO comments:"
grep -rI --color=auto --exclude="progress.sh" "TODO" src/ tools/ 2>/dev/null

echo ""
source_todo_count=$(grep -rI --exclude="progress.sh" "TODO" src/ tools/ 2>/dev/null | wc -l)
echo "Source TODO Count: $source_todo_count"

