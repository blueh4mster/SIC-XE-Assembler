## Introduction

The Objective of the project is to implement a version of two-pass SIC/XE assembler.

## Features implemented:

> - Literals
> - Control sections
> - Expressions
> - Assembler directives
> - Symbols

### Some conditions required for successfully running the code (to enforce best practices):

> - A comment must follow after a CSECT command (by specifying a . after the CSECT instruction).
> - Operands separated by commas (such as the ones found in EXTDEF and EXTREF) must not contain whitespace between them.

## Instructions

**Clone the repository**

```bash
git clone https://github.com/blueh4mster/SIC-XE-Assembler.git
```

**Run the assembler**

```bash
./run.sh
```

![image_](./WhatsApp%20Image%202024-04-12%20at%2000.18.17.jpeg)

**Note: If permission issue arises while running `./run.sh`, simply run `chmod +x ./run.sh`**
