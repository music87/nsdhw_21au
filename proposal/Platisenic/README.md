# Basic Information
- GitHub repository: https://github.com/Platisenic/autodiff
- Proejct Name: autodiff
# Problem to Solve
It is very important to compute the derivative of a function when we dealing with some optimization problems. With this method, we can find the input that maximize or minimize the function.

There are some methods for the computation of derivatives in computer programs. I would like to introduce [Numerical differentiation](https://en.wikipedia.org/wiki/Numerical_differentiation) and [Automatic differentiation](https://en.wikipedia.org/wiki/Automatic_differentiation), and implement Automatic differentiation.

### Numerical differentiation
Use the formula below to calculate the derivative  of a function.<br /><br />
![](https://latex.codecogs.com/svg.image?\lim_{h%20\to%200}%20\frac{f(x+h)-f(x)}{h}%20)<br /><br />
It is easy to implement, just substitute **h** with a small number like ![](https://latex.codecogs.com/svg.image?10^{-6}). Since **h** is too small and we substitute **h** with a finite number, computers will end up facing [Round-off error](https://en.wikipedia.org/wiki/Round-off_error) and [Truncation error](https://en.wikipedia.org/wiki/Truncation_error).

### Automatic differentiation
Automatic differentiation separate the complicated function to a sequence of elementary arithmetic operations and elementary functions. And for such operations we already know the functional form of the derivative. By applying the [chain rule](https://en.wikipedia.org/wiki/Chain_rule), we can compute the derivative of the complicated function correctly, and not occur errors like Numerical differentiation.

# Prospective Users
People who deal with some optimization problems that use Gradient-based algorithms. For example, [Gradient descent](https://en.wikipedia.org/wiki/Gradient_descent) is an optimization algorithm which is commonly-used to train [machine learning](https://en.wikipedia.org/wiki/Machine_learning) models and neural networks. It calculates the derivatives of the loss function and update the paramaters to minimize the loss.

# System Architecture
### Implementation detail
- In order to separate the complicated function, I use computation graph to represent the function. <br />
For example, ![](https://latex.codecogs.com/svg.image?y=(x1+x2)*x1). Computation graph is below. <br /> <br />
![dag](https://user-images.githubusercontent.com/69299037/137633802-6692a41b-c5c4-4bf9-bfb1-efadd27db00e.jpg)

- There are different type of nodes (class):
    - Variables
    - Constant
    - Operators
        - add
        - subtract
        - multiply
        - divide
- Members in nodes:
    - value: store value
    - grad: store gradient
    - input1: store input node
    - input2: store input node
    - output: store output node
- Member functions in Operators:
    - forward(*input): calculate the value during forward pass
    - backward(*input): calculate the gradient by chain rule during backward pass
- There is a compute engine that traverse the computation graph, and calculate the values, gradients of nodes.
    - Since the computation graph has dependencies (You can not traverse (+node) earlier than (x1 node) ), and it is a [Directed Acyclic Graph](https://en.wikipedia.org/wiki/Directed_acyclic_graph), the compute engine traverse the graph by order in [topological sort](https://en.wikipedia.org/wiki/Topological_sorting)
    - DAG can be implemented using structure called Node, and there are two input and one output inside the Node.
- Using [Operator Overloading](https://en.cppreference.com/w/cpp/language/operators), users not need to build the computation graph themselves.
### Work Flow
![workflow](https://user-images.githubusercontent.com/69299037/137633832-1fe5f554-0171-46f9-9b3f-de1211f3e56b.jpg)

# API Description
- Autodiff(inputvalues, function definitation): return the gradient of input values and the final result.
# Engineering Infrastructure
- Build system: use Makefile and support the following commands
    - make
    - make run
    - make test
    - make clean
- Testing framework:
    - C++: Google Test
    - Python: pytest
- Version Control:
    - git

# Schedule
- Week 1: Define node class
- Week 2: Implement member functions(get, set, operator overloading)
- Week 3: Implement topological sort
- Week 4: Implement forward pass
- Week 5: Implement backward pass
- Week 6: Testing
- Week 7: Fix bugs
- Week 8: Prepare Presentation
# References
[1] [Numerical differentiation](https://en.wikipedia.org/wiki/Numerical_differentiation) <br />
[2] [Automatic differentiation in machine learning: a survey](https://arxiv.org/abs/1502.05767) <br />
[3] [Round-off error](https://en.wikipedia.org/wiki/Round-off_error) <br />
[4] [Truncation error](https://en.wikipedia.org/wiki/Truncation_error) <br />
[5] [Chain rule](https://en.wikipedia.org/wiki/Chain_rule) <br />
[6] [Gradient descent](https://en.wikipedia.org/wiki/Gradient_descent) <br />
[7] [Machine learning](https://en.wikipedia.org/wiki/Machine_learning) <br />
[8][ Directed acyclic graph](https://en.wikipedia.org/wiki/Directed_acyclic_graph) <br />
[9] [topological sort](https://en.wikipedia.org/wiki/Topological_sorting) <br />
[10] [Operator Overloading](https://en.cppreference.com/w/cpp/language/operators) <br />
