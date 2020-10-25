# 註：

1.	輸出為升冪排序，而非降冪排序。
2.	除了 `HW1.v1.pdf` 及 `範例測資.txt` 中的 Case 外，還有一種 Case 為相同 ICD 但住院的時段不連續、不交錯且不包含於，此時需要將住院天數相加。

如：

**Input:**

bb3c6b59efb8,20200101,20200102,A391,,<br>
bb3c6b59efb8,20200104,20200106,A391,,

**Output:**

bb3c6b59efb8,A391,5

---
# Log

**2020/10/25 - v2**

1. **struct : node**
+ use smart pointer instead
+ add two constructor

2. **class : MyList**
+ use smart pointer instead<br>
+ remove destructor : ~MyList()<br>
+ remove function : pop_back()<br>

3. **separate functions involving implement a list from other functions**