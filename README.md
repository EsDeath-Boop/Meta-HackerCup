# Meta Hacker Cup — Round 1

Repository: **EsDeath-Boop / Meta-HackerCup-Round-1**

Short and sweet: this repo contains my solutions, notes and submission scripts for Round 1 of the Meta Hacker Cup. I used this challenge to practice algorithmic problem solving, optimise for speed, and learn how to structure contest submissions cleanly.

---

## Contents

* `solutions/` — my submitted solution files (one per problem).
* `tests/` — small input / output samples and local test harnesses where available.
* `scripts/` — helper scripts for compiling, running and packaging submissions.
* `notes/` — short write-ups, reasoning, and complexity analysis for each problem.
* `README.md` — this file.

> If a folder doesn't exist yet, treat the list above as suggested structure to keep the repo tidy.

---

## Languages & tools

Most solutions are written in C++ (fast + common in contests). If you spot solutions in other languages, they'll be clearly named (e.g., `solution_py/` for Python). Example toolchain commands below assume a Unix-like environment.

---

## Quick start

### Compile a C++ solution

```bash
# compile a single solution (replace PROBLEM with the filename without extension)
g++ -O2 -std=gnu++17 solutions/PROBLEM.cpp -o build/PROBLEM

# run against a local test input
./build/PROBLEM < tests/PROBLEM_input.txt > out.txt
```

### Run Python (if any)

```bash
python3 solutions/PROBLEM.py < tests/PROBLEM_input.txt > out.txt
```

---

## Style & conventions

* Filenames follow `PROBLEM_LANGUAGE.ext` when I include multiple versions (e.g. `a_cpp.cpp`, `a_py.py`).
* `notes/PROBLEM.md` contains the idea, complexity, and pitfalls.
* Solutions aim for clarity and contest performance; prefer `O(n log n)` or better where possible.

---

## My Round 1 performance

This contest was a blast. Quick summary:

* I solved several problems during the round and pushed my solutions here.
* I got **one question wrong** during the contest (I left a corner case unchecked).
* Final placement: **rank 707 in the Human track**.

I’m including the wrong attempt and the corrected approach in `notes/` so future me (and you) can learn from the mistake.

---

## Notes on the incorrect submission

* The incorrect solution failed on a corner case involving (small / empty / boundary) input values — see `notes/PROBLEM.md` for the detailed failure case and the corrected solution.
* Lesson learned: always sanity-check boundary constraints and add targeted tests for extremes.

---

## Contributing

If you want to suggest improvements, open an issue or a pull request. Small PR checklist:

1. Add or improve tests in `tests/`.
2. Keep formatting consistent and add comments for tricky parts.
3. Update `notes/` with explanation for algorithmic changes.

---

## License

This repo is provided for learning purposes. Use as you like — attribution appreciated.

---

## Contact / Author

**ES Death / EsDeath-Boop** — thanks for checking out my contest work. If you want to share feedback or improvements, open an issue or reach out on GitHub.

Good luck and happy coding! 🚀
