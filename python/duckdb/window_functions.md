# Window Functions

## Example
```sql
-- 计算销量环比增幅
SELECT amount / lag(amount) OVER (ORDER BY time) FROM sales;

-- 计算每一行的销量占所属地区的销量百分比
SELECT amount / sum(amount) OVER (PARTITION BY region) FROM sales;

-- 计算差分
SELECT amount - lag(amount) OVER (ORDER BY time) FROM sales;

```

## LAG函数
在 SQL 中，```LAG``` 函数是一种窗口函数，**它用于访问结果集中当前行的前面的行中的数据**。它常常用于分析数据中的时间序列或其他按照某种顺序排列的数据。```LAG``` 函数允许你在查询结果中回看若干行，并从中提取信息，非常适合用来进行数据比较或计算数据变化。

### 语法
```LAG``` 函数的基本语法如下：
```sql
LAG(expression, offset, default) OVER (partition_order_by_clause)
```
+ **expression**: 这是你希望从前面的行中获取的字段或计算表达式。
+ **offset**: 这是一个可选参数，用于指定你想要回看多少行。默认值是 1，表示回看前一行。
+ **default**: 这也是一个可选参数，用来定义当没有足够的行可供回看时的返回值（即当前行之前的行数少于指定的 offset）。如果未指定，当没有可回看的行时，默认返回 `NULL` 。
+ **partition_order_by_clause**: 这定义了 `LAG` 函数操作的数据窗口。它通常包含 `ORDER BY` 子句来指定数据的排序方式，也可以包含 `PARTITION BY` 子句来分组数据。

### 示例

当输入如下查询语句，查询股票数据的差分
```sql
SELECT 
    date,
    InnerCode,
    close,
    close - LAG(close, 1, NULL) OVER (PARTITION BY InnerCode ORDER BY date) AS close_change
FROM 
    stk_day
WHERE
    date >= '2019-01-01' AND date <= '2019-01-07'
```

返回结果如下：

| date                |   InnerCode |   close |   close_change |
|:--------------------|------------:|--------:|---------------:|
| 2019-01-02 00:00:00 |          85 |    7.16 |         nan    |
| 2019-01-03 00:00:00 |          85 |    7    |          -0.16 |
| 2019-01-04 00:00:00 |          85 |    7.12 |           0.12 |
| 2019-01-07 00:00:00 |          85 |    7.15 |           0.03 |
| 2019-01-02 00:00:00 |           3 |    9.19 |         nan    |
| 2019-01-03 00:00:00 |           3 |    9.28 |           0.09 |
| 2019-01-04 00:00:00 |           3 |    9.75 |           0.47 |
| 2019-01-07 00:00:00 |           3 |    9.74 |          -0.01 |

## LEAD函数
在 SQL 中，`LEAD` 函数是与 `LAG` 函数相对的另一种窗口函数，**它用于访问结果集中当前行的后面的行中的数据**。这种函数非常适用于需要提前查看数据或对数据进行前瞻性分析的情况。

### 语法

`LEAD` 函数的基本语法如下：
```sql
LEAD(expression, offset, default) OVER (partition_order_by_clause)
```
+ **expression**: 这是你希望从后面的行中获取的字段或计算表达式。
+ **offset**: 这是一个可选参数，用于指定你想要向前查看多少行。默认值是 1，表示查看后一行。
+ **default**: 这也是一个可选参数，用来定义当没有足够的行可供向前查看时的返回值（即当前行之后的行数少于指定的 `offset`）。如果未指定，当没有可向前查看的行时，默认返回 NULL。
+ **partition_order_by_clause**: 这定义了 `LEAD` 函数操作的数据窗口。它通常包含 `ORDER BY` 子句来指定数据的排序方式，也可以包含 `PARTITION BY` 子句来分组数据。

### 适用场景
`LEAD` 函数的使用场景包括但不限于：

预测分析，比如预测未来销售额或股票价格变动。
计算时间序列数据的变化，比如温度、汇率、网站访问量的未来趋势。
进行时间偏移的数据对比，例如在电影评分中比较观众对连续电影的评价差异。
通过使用 `LEAD` 和 `LAG`，可以实现复杂的数据分析任务，包括时间序列数据的前后比较，以及基于过去或未来数据点的预测和分析。这两个函数在数据处理和分析领域中都非常重要，它们增强了 SQL 查询的能力，使之能够解决更多高级的问题。

### 示例
如果希望计算某些股票未来一天的简单收益率，可以通过如下语句计算查询
```sql
SELECT 
    date,
    InnerCode,
    close,
    (LEAD(close, 1, NULL) OVER (PARTITION BY InnerCode ORDER BY date) - close) / close AS return_rate
FROM 
    stk_day
WHERE
    date >= '2019-01-01' AND date <= '2019-01-07'
```

| date                |   InnerCode |   close |   return_rate |
|:--------------------|------------:|--------:|---------------:|
| 2019-01-02 00:00:00 |          85 |    7.16 |    -0.0223464  |
| 2019-01-03 00:00:00 |          85 |    7    |     0.0171429  |
| 2019-01-04 00:00:00 |          85 |    7.12 |     0.00421348 |
| 2019-01-07 00:00:00 |          85 |    7.15 |   nan          |
| 2019-01-02 00:00:00 |           3 |    9.19 |     0.00979325 |
| 2019-01-03 00:00:00 |           3 |    9.28 |     0.0506466  |
| 2019-01-04 00:00:00 |           3 |    9.75 |    -0.00102564 |
| 2019-01-07 00:00:00 |           3 |    9.74 |   nan          |

在这个查询中:
+ `LEAD(close, 1, NULL) OVER (PARTITION BY InnerCode ORDER BY date)`计算得到每个股票一天后的收盘价，其中`PARTITION BY InnerCode`通过股票代码来区分不同股票，用`ORDER BY date`指定了窗口函数的排序方式
+ 如果最后一行没有后一行，`LEAD` 函数将返回 `NULL`，从而使 `return_rate` 为 `NULL`。

## FIRST_VALUE函数
`FIRST_VALUE` 是一个窗口函数，它从定义的窗口中返回第一个值，基于指定的排序顺序。这个函数非常有用，尤其是在需要从每个分组中提取最初记录的情景中。

### 示例
通过 `FIRST_VALUE` 函数查询分组中的第一个值
```sql
SELECT 
    date,
    InnerCode,
    close,
    FIRST_VALUE(close) OVER (PARTITION BY InnerCode ORDER BY date) AS first_row
FROM 
    stk_day
WHERE
    date >= '2019-01-01' AND date <= '2019-01-07'
```

返回结果如下:
| date                |   InnerCode |   close |   first_row |
|:--------------------|------------:|--------:|------------:|
| 2019-01-02 00:00:00 |          85 |    7.16 |        7.16 |
| 2019-01-03 00:00:00 |          85 |    7    |        7.16 |
| 2019-01-04 00:00:00 |          85 |    7.12 |        7.16 |
| 2019-01-07 00:00:00 |          85 |    7.15 |        7.16 |
| 2019-01-02 00:00:00 |           3 |    9.19 |        9.19 |
| 2019-01-03 00:00:00 |           3 |    9.28 |        9.19 |
| 2019-01-04 00:00:00 |           3 |    9.75 |        9.19 |
| 2019-01-07 00:00:00 |           3 |    9.74 |        9.19 |

## LAST_VALUE函数
`LAST_VALUE`函数与`FIRST_VALUE`函数用法大致相同，不同的是，其获取的是窗口中的最后一个值
