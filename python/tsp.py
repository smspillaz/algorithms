from collections import defaultdict, namedtuple


from Queue import Queue


CityNode = namedtuple("CityNode", "n cost")


def nightRoute(city):
    """Breadth first search here"""
    destCity = len(city) - 1
    bestCost = 999999999999999999999999
    seen_list = defaultdict(lambda: 9999999999999999999)
    q = Queue()
    for c, cost in enumerate(city[0]):
        if cost == -1:
            continue
        q.put(CityNode(c, cost))
    while not q.empty():
        current = q.get()
        if seen_list[current.n] < current.cost:
            continue
        seen_list[current.n] = current.cost
        if current.n == destCity:
            bestCost = current.cost
        else:
            for c, cost in enumerate(city[current.n]):
                if cost == -1:
                    continue

                print("Put city %i %i from %i\n", c, cost + current.cost, current.n)
                q.put(CityNode(c, current.cost + cost))
    return bestCost



