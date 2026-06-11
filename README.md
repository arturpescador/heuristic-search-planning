# Heuristic Search & Planning — List 3

**Universidade Federal do Rio Grande do Sul** \
Programa de Pós-Graduação em Computação \
Inteligência Artificial Avançada — 2026/1

## Build

```bash
python3 fast-downward/build.py
```

## Unit tests (AND/OR graph)

```bash
./fast-downward/builds/release/bin/downward --test-and-or-graphs
```

## Search

```bash
# Blind A*
python3 fast-downward/fast-downward.py <domain> <problem> --search "astar(blind())"

# A* + RTG (dead-end detection)
python3 fast-downward/fast-downward.py <domain> <problem> --search "astar(planopt_relaxed_task_graph())"

# Greedy h^add
python3 fast-downward/fast-downward.py <domain> <problem> --search "eager_greedy([planopt_add()])"

# Greedy h^FF
python3 fast-downward/fast-downward.py <domain> <problem> --search "eager_greedy([planopt_ff()])"
```

Results are written to `sas_plan` in the current directory.

## Example

```bash
python3 fast-downward/fast-downward.py castle/domain.pddl castle/castle-5-4-9-cards.pddl \
  --search "eager_greedy([planopt_ff()])"
```
