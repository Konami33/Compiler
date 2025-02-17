
### Code Overview:
The code evaluates an arithmetic expression using two stacks:
1. **`values` stack**: Stores the operands (numbers).
2. **`ops` stack**: Stores the operators (`+`, `-`, `*`, `/`, `%`) and parentheses.

The code processes the expression character by character, respecting operator precedence and parentheses.

---

### Example Walkthrough:
#### Input Expression: `2+2+2+2*2/2+2-2`

#### Step-by-Step Execution:

1. **Initialization**:
   - `values` stack: `[]`
   - `ops` stack: `[]`
   - `current_expression`: `"2+2+2+2*2/2+2-2"`

2. **Processing the Expression**:
   - The code iterates through each character of the expression.

---

#### Step 1: Process `2`
   - `2` is a digit, so it is parsed as a number.
   - `values` stack: `[2]`
   - `ops` stack: `[]`
   - `current_expression`: `"2+2+2+2*2/2+2-2"`

---

#### Step 2: Process `+`
   - `+` is an operator. Since the `ops` stack is empty, it is pushed onto the stack.
   - `values` stack: `[2]`
   - `ops` stack: `['+']`
   - `current_expression`: `"2+2+2+2*2/2+2-2"`

---

#### Step 3: Process `2`
   - `2` is a digit, so it is parsed as a number.
   - `values` stack: `[2, 2]`
   - `ops` stack: `['+']`
   - `current_expression`: `"2+2+2+2*2/2+2-2"`

---

#### Step 4: Process `+`
   - `+` is an operator. The top of the `ops` stack (`+`) has the same precedence, so the previous operation (`2 + 2`) is evaluated.
   - Pop `2` and `2` from `values`, and `+` from `ops`.
   - Compute `2 + 2 = 4` and push `4` onto `values`.
   - Push the new `+` onto `ops`.
   - Update `current_expression`:
     - Replace `2+2` with `4`.
     - `current_expression`: `"4+2+2*2/2+2-2"`
   - `values` stack: `[4]`
   - `ops` stack: `['+']`

---

#### Step 5: Process `2`
   - `2` is a digit, so it is parsed as a number.
   - `values` stack: `[4, 2]`
   - `ops` stack: `['+']`
   - `current_expression`: `"4+2+2*2/2+2-2"`

---

#### Step 6: Process `+`
   - `+` is an operator. The top of the `ops` stack (`+`) has the same precedence, so the previous operation (`4 + 2`) is evaluated.
   - Pop `2` and `4` from `values`, and `+` from `ops`.
   - Compute `4 + 2 = 6` and push `6` onto `values`.
   - Push the new `+` onto `ops`.
   - Update `current_expression`:
     - Replace `4+2` with `6`.
     - `current_expression`: `"6+2*2/2+2-2"`
   - `values` stack: `[6]`
   - `ops` stack: `['+']`

---

#### Step 7: Process `2`
   - `2` is a digit, so it is parsed as a number.
   - `values` stack: `[6, 2]`
   - `ops` stack: `['+']`
   - `current_expression`: `"6+2*2/2+2-2"`

---

#### Step 8: Process `*`
   - `*` is an operator with higher precedence than `+`, so it is pushed onto the stack.
   - `values` stack: `[6, 2]`
   - `ops` stack: `['+', '*']`
   - `current_expression`: `"6+2*2/2+2-2"`

---

#### Step 9: Process `2`
   - `2` is a digit, so it is parsed as a number.
   - `values` stack: `[6, 2, 2]`
   - `ops` stack: `['+', '*']`
   - `current_expression`: `"6+2*2/2+2-2"`

---

#### Step 10: Process `/`
   - `/` is an operator with the same precedence as `*`. The previous operation (`2 * 2`) is evaluated.
   - Pop `2` and `2` from `values`, and `*` from `ops`.
   - Compute `2 * 2 = 4` and push `4` onto `values`.
   - Push `/` onto `ops`.
   - Update `current_expression`:
     - Replace `2*2` with `4`.
     - `current_expression`: `"6+4/2+2-2"`
   - `values` stack: `[6, 4]`
   - `ops` stack: `['+', '/']`

---

#### Step 11: Process `2`
   - `2` is a digit, so it is parsed as a number.
   - `values` stack: `[6, 4, 2]`
   - `ops` stack: `['+', '/']`
   - `current_expression`: `"6+4/2+2-2"`

---

#### Step 12: Process `+`
   - `+` is an operator with lower precedence than `/`. The previous operation (`4 / 2`) is evaluated.
   - Pop `2` and `4` from `values`, and `/` from `ops`.
   - Compute `4 / 2 = 2` and push `2` onto `values`.
   - Push `+` onto `ops`.
   - Update `current_expression`:
     - Replace `4/2` with `2`.
     - `current_expression`: `"6+2+2-2"`
   - `values` stack: `[6, 2]`
   - `ops` stack: `['+', '+']`

---

#### Step 13: Process `2`
   - `2` is a digit, so it is parsed as a number.
   - `values` stack: `[6, 2, 2]`
   - `ops` stack: `['+', '+']`
   - `current_expression`: `"6+2+2-2"`

---

#### Step 14: Process `-`
   - `-` is an operator with the same precedence as `+`. The previous operation (`6 + 2`) is evaluated.
   - Pop `2` and `6` from `values`, and `+` from `ops`.
   - Compute `6 + 2 = 8` and push `8` onto `values`.
   - Push `-` onto `ops`.
   - Update `current_expression`:
     - Replace `6+2` with `8`.
     - `current_expression`: `"8+2-2"`
   - `values` stack: `[8, 2]`
   - `ops` stack: `['+', '-']`

---

#### Step 15: Process `2`
   - `2` is a digit, so it is parsed as a number.
   - `values` stack: `[8, 2, 2]`
   - `ops` stack: `['+', '-']`
   - `current_expression`: `"8+2-2"`

---

#### Step 16: End of Expression
   - The expression has been fully processed. Now, evaluate any remaining operations in the stacks:
     - Pop `2` and `8` from `values`, and `+` from `ops`.
     - Compute `8 + 2 = 10` and push `10` onto `values`.
     - Update `current_expression`:
       - Replace `8+2` with `10`.
       - `current_expression`: `"10-2"`
     - `values` stack: `[10, 2]`
     - `ops` stack: `['-']`

     - Pop `2` and `10` from `values`, and `-` from `ops`.
     - Compute `10 - 2 = 8` and push `8` onto `values`.
     - Update `current_expression`:
       - Replace `10-2` with `8`.
       - `current_expression`: `"8"`
     - `values` stack: `[8]`
     - `ops` stack: `[]`

---

#### Final Result:
   - The final result is the top of the `values` stack: `8`.

---

### Output:
```
2+2+2+2*2/2+2-2
4+2+2*2/2+2-2
6+2*2/2+2-2
6+4/2+2-2
6+2+2-2
8+2-2
10-2
8
Final result: 8
```

---

### Summary:
- The code correctly evaluates the expression by respecting operator precedence and associativity.
- It updates the expression step by step, showing the intermediate results.
- The final result is `8`, which is correct for the given input.