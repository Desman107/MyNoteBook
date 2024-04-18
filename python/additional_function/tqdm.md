# tqdm库:好用的python进度条

tqdm是一个可以显示python程序运行进度的库
导入库
```python
from tqdm.auto import tqdm
```

## 使用方法
1. 先指定循环长度
    ```python
    from tqdm.auto import tqdm
    import time
    #指定循环的长度
    pbar = tqdm(total = len(range(100)))
    for i in range(100):
        time.sleep(0.1)

        #更新进度条
        pbar.update(1)
    
    #循环结束后关闭进度条
    pbar.close()
    ```
    20%|-----&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| 187/972 [00:00<?, ?it/s]

&nbsp;&nbsp;

1. 使用tqdm包裹迭代器
    ```python
    from tqdm.auto import tqdm
    import time
    for i in tqdm(range(100)):
        time.sleep(0.01)
    ```
    20%|-----&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| 187/972 [00:00<?, ?it/s]