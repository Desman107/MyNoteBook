# (python) joblib.Memory ：用于加速函数计算的强大方法
joblib 是一个 Python 库，主要用于提供轻松的并行计算和有效的输入/输出操作。它特别适合用于在 Python 中执行重复的工作，如机器学习中经常需要的模型训练。

其中，Memory 类是 joblib 的一个重要组件，它提供了一个透明的磁盘缓存功能。Memory 的主要目的是缓存那些耗时的函数的输出，**以便在下次使用相同输入调用该函数时可以快速获取结果**，而不是重新计算。
&nbsp;&nbsp;



## 使用步骤
Memory 类的使用通常包括以下几个步骤：

1. **初始化**：创建一个 Memory 对象，指定一个目录用于存储缓存数据。
2. **装饰函数**：使用 Memory 对象的 cache 方法来装饰那些计算成本高、调用频繁的函数。
3. **调用函数**：在代码中正常调用这些函数，joblib 会自动检查是否已经缓存了给定输入的输出。如果已缓存，则直接从磁盘读取结果；如果未缓存，执行函数并将结果保存到磁盘上。
&nbsp;&nbsp;

## 示例代码
```python
from joblib import Memory
import time

# 创建 Memory 实例，指定缓存目录
cachedir = './joblib_cache'
mem = Memory(cachedir)

# 定义一个可能需要缓存的函数
@mem.cache
def slow_function(n):
    time.sleep(2)  # 模拟耗时操作
    return n * n

# 调用函数
result = slow_function(4)
print(result)

# 再次调用相同参数的函数
result = slow_function(4)  # 这次调用将直接从缓存中读取结果
print(result)

```

## Memory 的适用场景
Memory 类特别适合于以下情形：

+ **数据预处理**：在数据科学和机器学习工作流中，数据预处理步骤往往非常耗时，使用 Memory 可以缓存这些步骤的结果，使得实验迭代更加快速。
+ **参数优化**：在模型训练和参数优化过程中，可能需要多次执行相同的计算，Memory 可以避免重复计算，节省大量时间。
+ **复杂计算**：对于任何需要重复执行并且计算代价高的函数，使用 Memory 可以显著提高效率。

## 注意事项
虽然 Memory 是一个非常有用的工具，但它也需要合理使用。缓存大量的数据可能会占用大量磁盘空间。此外，**如果函数的内部逻辑发生了变化，需要清除缓存以防止使用过时的结果**。

总之，joblib 的 Memory 类是一个强大的工具，可以在Python中有效地管理和缓存耗时的计算结果，特别是在数据分析和机器学习领域中。

## 清除缓存

```python
from joblib import Memory

cachedir = './joblib_cache'
mem = Memory(cachedir)

@mem.cache
def some_function(x):
    return x * x

# 假设你改变了函数逻辑
@mem.cache
def some_function(x):
    return x + x

# 清理特定函数的缓存
mem.clear(warn=True)
```

注意```'./joblib_cache'```文件夹下的所有文件都将被清空，建议不要放除了缓存外的任何数据在此文件夹下