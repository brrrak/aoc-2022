from ast import literal_eval
from functools import cmp_to_key, reduce

def compare(l, r):
    """
    Returns:
        -1 if right order
        1 if wrong order
        0 if inconclusive
    """
    if type(l) == int and type(r) == int:
        return 0 if l == r else (-1 if l < r else 1)
    elif type(l) == list and type(r) == list:
        for new_l, new_r in zip(l, r):
            res = compare(new_l, new_r)
            if res != 0:
                return res
        return 0 if len(l) == len(r) else (-1 if len(l) < len(r) else 1)
    else:
        l = [l] if type(l) == int else l
        r = [r] if type(r) == int else r
        return compare(l, r)

def main():
    with open("./input.txt", 'r') as f:
        pairs = ''.join(f.readlines()).split("\n\n")
    
    right_order_pairs = []
    for i, pair in enumerate(pairs, start=1):
        left, right = map(literal_eval, pair.strip().split('\n'))
        res = compare(left, right)
        if res == -1:
            right_order_pairs.append(i)

    print(f"Part 1 Answer: {sum(right_order_pairs)}")

    packets = [item for sublist in pairs for item in sublist.strip().split('\n')]
    packets.extend(["[[2]]", "[[6]]"])
    packets = sorted(list(map(literal_eval, packets)), key=cmp_to_key(compare))

    dividers = [[[2]], [[6]]]
    div_indices = [i for i, packet in enumerate(packets, start=1) if packet in dividers]
    decoder_key = reduce(lambda x, y: x * y, div_indices)

    print(f"Part 2 Answer: {decoder_key}")

if __name__ == "__main__":
    main()