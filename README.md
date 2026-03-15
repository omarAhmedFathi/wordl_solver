# Wordle Entropy Solver (C)

This project is a **Wordle solver written in C** that uses **Information Theory** to determine the best possible guess.

The algorithm calculates **Shannon entropy** for each possible guess and selects the word that maximizes **information gain**, which reduces the number of remaining candidate words as efficiently as possible.

---

# Project Structure

```
project/
│
├── wordl_solver.c   # Main solver program
├── data.c           # Contains dictionary and target word lists
├── README.md
```

---

# Requirements

You need the following:

* GCC compiler
* Linux / Ubuntu / MacOS
* Math library (`-lm`)

Install GCC on Ubuntu:

```
sudo apt install build-essential
```

---

# Compilation

Compile the program using:

```
gcc wordl_solver.c data.c -lm -o solver
```

Explanation:

| Part           | Meaning           |
| -------------- | ----------------- |
| wordl_solver.c | main program      |
| data.c         | word database     |
| -lm            | link math library |
| -o solver      | output executable |

---

# Running the Program

Run the solver:

```
./solver
```

Example output:

```
Loading...

Prior entropy H(W) = 11.66
Expected posterior entropy H(W|Y) = 5.23
Information gain I(W;Y) = 6.43
Remaining candidates length :3241
Best-guess feedback entropy H(Y) = soare
```

After the guess, enter the **Wordle feedback pattern**.

```
g = green
y = yellow
r = gray
```

Example input:

```
rygry
```

The solver will update the candidate list and compute the next best guess.

---

# Information Theory Used

The solver uses **Shannon entropy** to measure uncertainty in the remaining word list.

Entropy formula:

```
H(X) = - Σ p(x) log₂ p(x)
```

Where:

* `p(x)` is the probability of an outcome
* higher entropy means more information

---

# Information Gain

Information gain measures how much uncertainty is reduced after a guess.

```
I(W;Y) = H(W) − H(W|Y)
```

Where:

* `H(W)` = entropy of the word list
* `H(W|Y)` = entropy after receiving feedback
* `I(W;Y)` = information gained from the guess

The solver selects the word that **maximizes information gain**.

---

# Wordle Feedback Encoding

Each letter in Wordle can produce three states:

| Symbol | Meaning                                  |
| ------ | ---------------------------------------- |
| g      | green (correct letter, correct position) |
| y      | yellow (correct letter, wrong position)  |
| r      | gray (letter not in word)                |

Since there are 5 letters and 3 states per letter:

```
3^5 = 243
```

possible feedback patterns.

The program encodes these patterns using **base-3 representation**.

---

# Algorithm Overview

1. Load dictionary and target word list
2. Precompute feedback patterns between all words
3. Compute frequency distribution of feedback patterns
4. Calculate entropy for each possible guess
5. Select the guess with maximum entropy
6. Filter possible answers
7. Repeat until one candidate remains

---

# Dataset Size

Dictionary words:

```
12969 words
```

Possible target words:

```
3241 words
```

---

# Complexity

Precomputation:

```
O(dictionary × target)
```

Entropy evaluation:

```
O(dictionary × 243)
```

---

# Example Session

```
Loading...

Prior entropy H(W) = 11.66
Information gain I(W;Y) = 5.9
Best guess = soare

Enter feedback: rrygr

Remaining candidates: 123
Next guess: ...
```

---

# Possible Improvements

Future improvements could include:

* multithreading
* SIMD optimization
* memory layout improvements
* GPU acceleration
* heuristic pruning

---

# Author

Engineering student interested in:

* Information Theory
* Optimization Algorithms
* High-performance computing
* Cybersecurity tools
