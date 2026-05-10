import sys
import re
from collections import defaultdict

# Reads piped input from Select-String
lines = sys.stdin.readlines()

# Match:
# <stuff>:<line>:<address> <size> <address> 0 <symbol>
pattern = re.compile(
    r'^.*?:\d+:([0-9a-fA-F]{8})\s+[0-9a-fA-F]+\s+[0-9a-fA-F]{8}\s+0\s+(.+)$'
)

groups = defaultdict(list)

for line in lines:
    line = line.strip()

    match = pattern.match(line)
    if not match:
        continue

    address = match.group(1)
    symbol = match.group(2)

    # Skip LOCAL/GUARD junk
    if symbol.startswith('@LOCAL@') or symbol.startswith('@GUARD@'):
        continue

    # Determine class/group name
    group = "GLOBAL"

    if "__" in symbol:
        split = symbol.split("__", 1)

        if len(split) > 1:
            right = split[1]

            # Extract class name before first F or end
            class_match = re.match(r'([^F]+)', right)

            if class_match:
                group = class_match.group(1)

    groups[group].append((symbol, address))

# Alphabetic group order
for group_name in sorted(groups.keys()):
    print("/* {} */".format(group_name))

    # Alphabetic symbol order
    sorted_symbols = sorted(groups[group_name], key=lambda x: x[0].lower())

    for symbol, address in sorted_symbols:
        print("{} = 0x{};".format(symbol, address.upper()))

    print()