from queue import Queue
from typing import List


class Monkey:
    items: Queue
    opp: str
    supplier: int
    test_by: int 
    hold_count: int = 0
    true_jump: int 
    false_jump: int 
    name: int 

    def simulate_focus(self, monkeys: List['Monkey']):
        while not self.items.empty():
            self.hold_count += 1

            # Pop an item off of the stack
            item = self.items.get()

            # Apply the monkey's operation to the item
            if self.opp == '*':
                item = item * self.supplier
            elif self.opp == '+':
                item = item + self.supplier
            elif self.opp == '^':
                item = item * item

            # Test the item's value
            if item % self.test_by == 0:
                # If the test is true, throw the item to the true_jump monkey
                throw_to = self.true_jump
            else:
                # Throw to false_jump monkey
                throw_to = self.false_jump

            monkeys[throw_to].items.put(item)

    def __init__(self, test_by: int, true_jump: int, false_jump: int, items: Queue, opp: str, supplier: int):
        self.test_by = test_by
        self.true_jump = true_jump
        self.false_jump = false_jump
        self.items = items
        self.opp = opp
        self.supplier = supplier


def main():
    monkeys = []
    starting_items0 = Queue()
    starting_items0.put(66)
    starting_items0.put(71)
    starting_items0.put(94)

    starting_items1 = Queue()
    starting_items1.put(70)

    starting_items2 = Queue()
    starting_items2.put(62)
    starting_items2.put(68)
    starting_items2.put(56)
    starting_items2.put(65)
    starting_items2.put(94)
    starting_items2.put(78)

    starting_items3 = Queue()
    starting_items3.put(89)
    starting_items3.put(94)
    starting_items3.put(94)
    starting_items3.put(67)

    starting_items4 = Queue()
    starting_items4.put(71)
    starting_items4.put(61)
    starting_items4.put(73)
    starting_items4.put(65)
    starting_items4.put(98)
    starting_items4.put(98)
    starting_items4.put(63)

    starting_items5 = Queue()
    starting_items5.put(55)
    starting_items5.put(62)
    starting_items5.put(68)
    starting_items5.put(61)
    starting_items5.put(60)

    starting_items6 = Queue()
    starting_items6.put(93)
    starting_items6.put(91)
    starting_items6.put(69)
    starting_items6.put(64)
    starting_items6.put(72)
    starting_items6.put(89)
    starting_items6.put(59)
    starting_items6.put(71)

    starting_items7 = Queue()
    starting_items7.put(76)
    starting_items7.put(50)



    monkey0 = Monkey(3, 7, 4, starting_items0, '*', 5)
    monkey1 = Monkey(17, 3, 0, starting_items1, '+', 6)
    monkey2 = Monkey(2, 3, 1, starting_items2, '+', 5)
    monkey3 = Monkey(19, 7, 0, starting_items3, '+', 2)
    monkey4 = Monkey(11, 5, 6, starting_items4, '*', 7)
    monkey5 = Monkey(5, 2, 1, starting_items5, '+', 7)
    monkey6 = Monkey(13, 5, 2, starting_items6, '+', 1)
    monkey7 = Monkey(7, 4, 6, starting_items7, '^', 1)

    monkeys.append(monkey0)
    monkeys.append(monkey1)
    monkeys.append(monkey2)
    monkeys.append(monkey3)
    monkeys.append(monkey4)
    monkeys.append(monkey5)
    monkeys.append(monkey6)
    monkeys.append(monkey7)

    for i in range(1000):
        for n in range(len(monkeys)):
            monkey = monkeys[n]
            monkey.simulate_focus(monkeys)
        print("Completed simulation ", i)

    for m in monkeys:
        print("Monkey ", m.name)
        print("Items: ", end="")
        while len(m.items) > 0:
            print(m.items.popleft(), " ", end="")
        print()
        print(m.hold_count)

main();