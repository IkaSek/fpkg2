# STYLING

## 1. Why are some names compliant to snake case, and why is most of the code base PASCAL case

Well, PASCAL case is the most comfortable for myself, however, snake case is for plugin-specific functionality.

## 2. Why do we have INT, UINT, FLOAT32, and FLOAT64 instead of Int, Uint, Float32, Float64

I like to scream my primitives.
Primitives are special types, thus, they shouldn't conform to Pascal case but, instead, they should use MACRO CASE,
altough, if you need more than a single descriptive word, it's not a primitive, rather, it's a **complex type**.
