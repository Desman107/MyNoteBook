现在有两张duckdb表格定义如下
CREATE TABLE IF NOT EXISTS stk_min(
    datetime TIMESTAMP,
    InnerCode INTEGER,
    money DECIMAL(20,5),
    volume DECIMAL(20,5),
    close DECIMAL(20,5),
    high DECIMAL(20,5),
    low DECIMAL(20,5),
    open DECIMAL(20,5),
    time VARCHAR(20),
    EventDate VARCHAR(20)
);
CREATE TABLE IF NOT EXISTS min_alpha001(
    datetime TIMESTAMP,
    InnerCode INT,
    EventDate DATE,
    return_1T DECIMAL(10,10),
    return_5T DECIMAL(10,10),
    return_15T DECIMAL(10,10),
    return_30T DECIMAL(10,10)
);
我希望根据stk_min表格的数据计算不同分钟时间间隔的的收益率，并将结果insert到min_alpha001表格中
对此，我写了这个sql语句但它有些问题，请问如何修改
def get_dql(date):
    dql = f"""
    INSERT INTO min_alpha001 AS
        SELECT
            datetime,
            InnerCode,
            EventDate,
            (LEAD(close,1,NULL) OVER(PARTITION BY InnerCode ORDER BY datetime) - close) / close  AS return_rate_1T,
            (LEAD(close,5,NULL) OVER(PARTITION BY InnerCode ORDER BY datetime) - close) / close  AS return_rate_5T,
            (LEAD(close,15,NULL) OVER(PARTITION BY InnerCode ORDER BY datetime) - close) / close  AS return_rate_15T,
            (LEAD(close,30,NULL) OVER(PARTITION BY InnerCode ORDER BY datetime) - close) / close  AS return_rate_30T
        FROM 
            stk_min
        WHERE
            EventDate ='{date}' 
        ORDER BY InnerCode,datetime;
    """
