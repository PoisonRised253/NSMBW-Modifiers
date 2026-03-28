#This was made entirely by chatgpt, because tired me decided to not waste my time figuring out python. I hate python.
import sys
import re

pattern = re.compile(r":([0-9a-fA-F]{8})\s+[0-9a-fA-F]{8}\s+[0-9a-fA-F]{8}\s+\d+\s+(\S+)")

matches = []

# Forbidden characters
forbidden_chars = ['@', '<', '>']

# Collect all matches
for line in sys.stdin:
    match = pattern.search(line)
    if match:
        addr = match.group(1).upper()
        symbol = match.group(2)
        # Skip symbols containing any forbidden character
        if any(c in symbol for c in forbidden_chars):
            continue
        matches.append((symbol, addr))

# Sort alphabetically, ignoring case
matches.sort(key=lambda x: x[0].lower())

print("\n\nStart!\n")
# Print sorted
for symbol, addr in matches:
    print(f"{symbol} = 0x{addr};")

print("\nAll Done!\n")