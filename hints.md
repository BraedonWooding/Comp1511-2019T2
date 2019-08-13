# Problem Hints

## Joining Lists

- Think about the base case
- It is quite a simple solution
- Think about it as you move curA forward howMany then move curB forward howMany and repeat, each time you move one of them forward your adding it to the list.

## Count Peaks

- You want to get relative indices from your current location
- Should just be similar to summing up the number of items in an array but with a condition

## Postfix Calculator

- Represent each number as a push operation
- Represent each symbol (i.e. '*', '/', '+', and '-') as two pop operations a, b (get the two numbers) then a push operation (the result of a symbol b i.e. a * b).

## Chess Moves

- For non unique:
  - For each piece check all places that it can move, if another enemy piece occupies that square than you have found a piece you can take
- For unique:
  - Do the same as above but have an array that stores all the pieces taken so far (perhaps just as a 2d array of true/false or 1/0) and if it already is taken don't take it again.
  - So not much harder but requires a little more intuitiion

## Big Int

- Store each digit as a single integer i.e. store an array of digits (ints).
- Store being positive/negative as a separate field
- Your struct should look something like;

```c
struct _big_int_t {
    int *num;
    int num_digits;
    int is_positive;
}
```

- Do addition/multiplication digit by digit
- Addition of negative numbers is a tad tricky especially when for a - b and a < b.  In that specific case I recommend doing the following; - (b - a) that way you won't have to do any weirdness with adding back the multiple of 10.  In the case when a >= b then there should be no issue.
- Think about having a carry flag to carry over any overflow from the previous addition for example for 3 + 9 you would have 2 in the first slot then carry = 1 which would be set to the next slot giving you 12.
- Subtraction should be as easy as changing the is_positive flag temporarily calling the addition then changing it back.

For example;

```c
BigInt subBigInt(BigInt a, BigInt b) {
    // x = x == 0 is just the same as invert x
    // or !x or if x is false make it true else
    // make it false

    // a - b => a + (-b)
    b->is_positive = b->is_positive == 0;
    BigInt tmp = addBigInt(a, b);
    b->is_positive = b->is_positive == 0;
    return tmp;
}
```

- Multiplication is quite tricky so be happy if you get addition correct!

## Balanced Braces

- Use a stack.
- For each opening bracket, brace, parenthesis you can push it onto the stack
- For each closing bracket, brace, parenthesis you can pop one of the stack and check if it is the opening version of the closing one you saw.  If it isn't then they don't balance
- At the end if your stack is empty then they balance

## Simplify Directory Path

- Kinda similar to above
- Use a stack, for each normal directory like `/home/a` push `home` and `a` onto the stack
- Ignore all `./` since they have no impact
- Ignore the last `/` for example `/home/` = `/home`
- Everytime you see a `..` you can just pop the top one of the stack and continue.
