> # 大师定理 #



> **分治**策略对应的递推式，**通常**（尽管**不总是**）形如：T（n）= **a** * T(n/**b**) + O(**f(n**))
>
> (原问题被分为**a**个规模均为**n/b**的子任务；任务的划分、解的合并耗时**f(n)**)
>
> 对于第一三区块，**T（n）中   f（n）  与     n ^ ( log(b) a )**  哪一个大就取哪一个

> 若 **f(n) = O(n^(log(b)a-ε))** , 则 **T(n) = Θ(n^(log(b)a))**
>
> - Kd-search : T(n) = **2** * T(n/**4**) + O(1) = O(**n^(1/2)**)

> 若 **f(n) = Θ(n^(log(b)a) * log^(k)n)** , 则 **T(n) = Θ(n^(log(b)a) * log^(k+1)n)**
>
> - Binary search: T(n) = **1** * T(n/**2**) + O(1) = O(**logn**)
> - Merge sort : T(n) = **2** * T(n/**2**) + O(**n**) = O(**n * logn**)
> - STL Merge sort : T(n) = **2** * T(n/**2**) + O(**n * logn**) = O(**n*(logn)^2**）

> 若 **f(n) = Ω(n^(log(b) a+ε)** , 则 **T(n) = Θ(f(n))**
>
> - Quick select (average case) : T(n) = **1** * T(n/**2**) + O(**n**)

