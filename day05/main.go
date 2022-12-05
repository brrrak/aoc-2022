package main

import (
	"fmt"
	"os"
	"strings"
)

type Stack []byte

func (s *Stack) IsEmpty() bool {
	return len(*s) == 0
}

func (s *Stack) Push(ch byte) {
	*s = append(*s, ch)
}

func (s *Stack) Pop() (byte, bool) {
	if s.IsEmpty() {
		return 0, false
	} else {
		i := len(*s) - 1
		item := (*s)[i]
		*s = (*s)[:i]
		return item, true
	}
}

func (s *Stack) PopInOrder(amount int) ([]byte, bool) {
	start := len(*s) - amount
	if s.IsEmpty() || start < 0 {
		return []byte{0}, false
	} else {
		items := (*s)[start:]
		*s = (*s)[:start]
		return items, true
	}
}

func solve(stacks []Stack, actioninput []string, isPart1 bool) {
	// Parsing actions
	for _, line := range actioninput {
		var amount, from, to int
		_, err := fmt.Sscanf(line, "move %v from %v to %v", &amount, &from, &to)
		if err != nil {
			continue
		}
		if isPart1 {
			for i := 0; i < amount; i++ {
				item, got_item := stacks[from-1].Pop()
				if !got_item {
					fmt.Println("Pop from empty stack!")
					break
				}
				stacks[to-1].Push(item)
			}
		} else {
			items, got_items := stacks[from-1].PopInOrder(amount)
			if !got_items {
				panic("Pop from empty stack!")
			}
			for _, item := range items {
				stacks[to-1].Push(item)
			}
		}
	}
}

func getStack(stackinput []string, num_of_stacks int) []Stack {
	// Parsing stack inputs
	stacks := make([]Stack, 0)
	for i := len(stackinput) - 2; i >= 0; i-- {
		line := stackinput[i]
		for j := 0; j < num_of_stacks; j++ {
			if i == len(stackinput)-2 { // initialize stacks
				stacks = append(stacks, make(Stack, 0))
			}
			ch := line[j*4+1]
			if ch != ' ' {
				stacks[j].Push(ch)
			}
		}
	}

	return stacks
}

func printResult(stacks []Stack) {
	for _, stack := range stacks {
		top, got_item := stack.Pop()
		if !got_item {
			fmt.Print("empty ")
			continue
		}
		fmt.Print(string(top))
	}
	fmt.Print("\n")
}

func main() {
	dat, err := os.ReadFile("./input.txt")
	if err != nil {
		panic(err)
	}
	input := strings.Split(string(dat), "\n\n")
	stackinput := strings.Split(input[0], "\n")
	actioninput := strings.Split(input[1], "\n")
	num_of_stacks := (len(stackinput[0]) + 1) / 4

	stacksA := getStack(stackinput, num_of_stacks)
	stacksB := getStack(stackinput, num_of_stacks)

	solve(stacksA, actioninput, true)
	solve(stacksB, actioninput, false)

	fmt.Print("Part 1 Answer: ")
	printResult(stacksA)
	fmt.Print("Part 2 Answer: ")
	printResult(stacksB)
}
