# Mô tả và giới thiệu:
* Project này thực hiện giao tiếp USB low speed trên dòng vi điều khiển STC8F sử dụng nhân 8051-1T
* Chương trình này có thể thực thi ngay trên STC8F2K08S2 và STC8F2K16S2 mà không cần chỉnh sửa gì thêm.
* Project được viết và biên dịch trên KeilC
# Thiết lập phần cứng cơ bản:
* Tần số hoạt động: 27MHz.
* D-: P3.0
* D+: P3.1 và P3.2 (P3.1 và P3.2 phải được nối vào nhau)
* Trở kéo 1.5K từ chân D- lên nguồn cấp (VCC)
* Nên sử dụng nguồn cấp 3.3V cho MCU để tối giản số lượng linh kiện cần để hỗ trợ thêm.
* Nếu sử dụng nguồn 5V bạn sẽ cần thêm trở mà diode zener 3.3V hoặc 3.6V để tạo mức logic
cho hai đường tín hiệu USB (Tham khảo sơ đồ nguyên lý này của mạch nạp ISP).
# Thông tin liên hệ:
* Facebook: https://www.facebook.com/electricthanhtung (thường xuyên kiểm tra)
* Email: electricthanhtung@gmail.com
