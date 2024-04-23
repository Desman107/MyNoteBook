<style>
pre {
  overflow-y: auto;
  max-height: 300px;
}
</style>
# Window Functions
SQL的窗口函数是一种非常强大的工具，用于进行复杂的数据分析和计算，而不需要将数据分组到多个输出行中。你可以在单个查询中完成排序、排名、累积等多种计算。窗口函数也称为OLAP（在线分析处理）函数。

## 基本概念
窗口函数在执行普通的SQL查询后对结果集进行操作。这意味着先执行FROM, JOIN, WHERE, GROUP BY, HAVING等语句，然后再应用窗口函数。窗口函数通过定义"窗口"（数据的子集），对这些子集执行计算。

## 关键术语
+ **窗口**：窗口是指定行的集合，这些行是与当前行在某种计算关系上相关联的。
+ **OVER()**：这是窗口函数的核心部分，用于定义窗口的分组方式、排序顺序和窗口的范围。

## 窗口函数语法
窗口函数的语法如下:
```sql
<window_function> OVER (
    PARTITION BY <column1>, <column2>, ...
    ORDER BY <column>
    [ROWS|RANGE BETWEEN <start> AND <end>]
)
```
+ `OVER(ORDER BY date)` 指定窗口的排序方式
+ `OVER(ROWS BETWEEN <start> AND <END>)`
  其中`<start>`和`<end>`可以是以下几种类型：
  + `UNBOUNDED PRECEDING`: 表示从分区的起始行开始。
  + `x PRECEDING`: 表示从当前行向前x行（不包括当前行本身），x必须是非负整数。
  + `CURRENT ROW`: 表示当前行。
  + `x FOLLOWING`: 表示从当前行向后x行（不包括当前行本身），x必须是非负整数。
  + `UNBOUNDED FOLLOWING`: 表示直到分区的结束行。
+ `OVER(PARTITION BY code)` 指定窗口的的分组方式，每个窗口是相互独立的

## 常用的窗口函数
1. **聚合窗口函数**：
+ `SUM() OVER()`
+ `AVG() OVER()`
+ `MIN() OVER()`
+ `MAX() OVER()`
这些函数可以在窗口内部对数据进行聚合计算。
2. **排名窗口函数**：
+ `ROW_NUMBER() OVER()`
+ `RANK() OVER()`
+ `DENSE_RANK() OVER()`
+ `NTILE(n) OVER()`
这些函数用于为数据集中的行分配一个唯一的排名。
3. **分析窗口函数**：
+ `LEAD(value, offset, default) OVER()`
+ `LAG(value, offset, default) OVER()`
+ `FIRST_VALUE() OVER()`
+ `LAST_VALUE() OVER()`
这些函数可以访问由窗口定义的行集中的前后行。

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

## NTILE函数
`NTILE()` 是 SQL 中的一种窗口函数，用于将有序分区中的行分成指定数量的近似等大小的组，并为每一行分配一个组号。这种分组是基于排序顺序来确定的。`NTILE()` 函数非常有用于执行分位数分析、数据分段、以及在统计分析中均匀切分数据集。

### 语法
`NTILE()` 函数的基本语法如下：
```sql
NTILE(number_of_tiles) OVER (
    [PARTITION BY partition_expression, ...]
    ORDER BY sort_expression [ASC|DESC], ...
)
```
+ `number_of_tiles`：一个正整数，定义要将数据分割成多少个组。
+ `PARTITION BY`：可选，按指定列的值对结果集进行分组。如果省略，整个结果集被视为一个单一的分区。
+ `ORDER BY`：定义如何对数据进行排序，排序的基础是分组的依据

### 工作原理
`NTILE()` 函数首先根据 `ORDER BY` 子句对数据进行排序。然后，根据 `number_of_tiles` 参数将这些排序后的数据分割成指定数量的组。如果数据总数不能被组数整除，那么前几个组将包含一个额外的数据行。

### 示例
使用 `NTILE()` 函数将股票的收盘价分为高和低两部分
```sql
SELECT 
    date,
    InnerCode,
    close,
    NTILE(2) OVER (PARTITION BY InnerCode ORDER BY close ROWS BETWEEN 4 PRECEDING AND CURRENT ROW) AS cluster
FROM 
    stk_day
WHERE
    date >= '2019-01-01' AND date <= '2019-01-15'
ORDER BY
    InnerCode,date
```
返回结果如下：
| date                |   InnerCode |   close |   cluster |
|:--------------------|------------:|--------:|------------:|
| 2019-01-02 00:00:00 |          85 |    7.16 |           1 |
| 2019-01-03 00:00:00 |          85 |    7    |           1 |
| 2019-01-04 00:00:00 |          85 |    7.12 |           1 |
| 2019-01-07 00:00:00 |          85 |    7.15 |           1 |
| 2019-01-08 00:00:00 |          85 |    7.2  |           2 |
| 2019-01-09 00:00:00 |          85 |    7.2  |           2 |
| 2019-01-10 00:00:00 |          85 |    7.24 |           2 |
| 2019-01-11 00:00:00 |          85 |    7.27 |           2 |
| 2019-01-14 00:00:00 |          85 |    7.14 |           1 |
| 2019-01-15 00:00:00 |          85 |    7.18 |           2 |