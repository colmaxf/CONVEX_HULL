# Convex Hull

Chương trình C++ này tính toán bao lồi của một tập hợp các điểm 2D bằng thuật toán Monotone Chain.

## Biên dịch

```bash
g++ -o convex_hull convex_hull.cpp
```

## Chạy chương trình

Chương trình nhận ba đối số dòng lệnh:
1.  `quantity`: Số lượng điểm ngẫu nhiên cần tạo.
2.  `min_value`: Giá trị tọa độ nhỏ nhất cho các điểm.
3.  `max_value`: Giá trị tọa độ lớn nhất cho các điểm.

Ví dụ:
```bash
./convex_hull 10 -10 10 
```

## Kết quả ví dụ

Chương trình sẽ tạo một tệp `coordinates.txt` với các điểm ngẫu nhiên, sau đó đọc tệp này, tính toán bao lồi và in kết quả ra màn hình console cũng như lưu vào tệp `hull_output.txt`.

```text
Processing... 10 coordinates and save as file coordinates.txt...
Create file coordinates.txt successfully.
Read file points.txt successfully: 10
(...danh sách các điểm được tạo...)
Convex Hull: 
(-1.9, -3.2)
(7.3, -5)
(8.3, -3.3)
(8.9, 4.9)
(1.6, 1.9)
Complete successfully
```