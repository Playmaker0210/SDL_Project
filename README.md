- Họ và tên: Nguyễn Mạnh Hùng
- MSV: 21020075

1. MÔ TẢ CHUNG VỀ TRÒ CHƠI:
- Điều khiển nhân vật di chuyển bằng các phím mũi tên. Bấm phím P để tạm dừng trò chơi. Bấm phím Z để tấn công bằng lửa, tiêu tốn 15 mana. Bấm phím X để tấn công bằng nước, tiêu tốn 10 mana. Khởi đầu với 3 mạng, mỗi mạng có 100 HP và 150 mana. Tiêu diệt quái vật trên đường đi và lấy ngôi sao để dành chiến thắng.Có thể sử dụng các item trên đường đi để hỗ trợ.

2. Ý TƯỞNG CHÍNH:
- Coi các đối tượng trong game( nhân vật chính, quái vật, đạn, các chướng ngại vật) là các hình chữ nhật trong hệ tọa độ Đề-các. Khi 2 hình chữ nhật đố tiếp xúc hay giao nhau thì hai đối tượng mà chúng đại diện va chạm với nhau. Bản đồ game bao gồm 400x10 tile, mỗi tile có kích thước 64px * 64px.

3. CÁC CHỨC NĂNG ĐÃ CÀI ĐẶT:
- Menu game
- Animation cho quái vật và nhân vật chính
- Cơ chế Pause game
- Cơ chế in ra điểm sau khi kết thúc trò chơi và lưu lại danh sách 5 số điểm cao nhất
- In ra màn hình các thông số của nhân vật như số điểm, số mạng còn lại, số HP và mana hiện có
- Nhận lệnh từ chuột và bàn phím để điều khiển game
- Có âm thanh
- Có thể chơi lại nhiều lần
- Cơ chế tăng 10 mana sau mỗi 3 giây trôi qua trong game
- Tile map
- Quái vật biết nhận dạng vị trí người chơi từ đó điểu chỉnh hướng bắn, di chuyển hoặc ngừng bắn.
- Link video demo: https://www.youtube.com/watch?v=2h4BsG1S4lE

4. CÁC KĨ THUẬT LÂP TRÌNH ĐÃ SỬ DỤNG:
- Struct và Class
- Con trỏ
- Vector
- Xâu
- Nhập/xuất file
- Mảng tĩnh
- Sắp xếp
- Lập trình hướng đối tượng

5. Kết luận:
- Học SDL và lí thuyết Tile Map tại: http://lazyfoo.net/tutorials/SDL/39_tiling/index.php và https://phattrienphanmem123az.com/
- Code hoàn toàn là tự viết.
- Thêm chức năng tắt âm thanh và chức năng Replay để chơi lại từ đầu.
- Thêm hiệu ứng và cải thiện "trí thông minh" của Boss.
- Thêm cơ chế chọn màn chơi.
- Thêm 1 vài item sẽ biến mất sau 1 khoảng thời gian nhất định
- Một số điều rút ra sau khi hoàn thiện bài làm:
   + Hiểu sâu hơn về class và khả năng kế thừa.
   + Biết chia và phân bố chương trình.
- Nhược điểm trong bài làm:
   + Hàm check va chạm được viết dựa theo ý tưởng kiểm tra xem 2 hình chữ nhật đại diện cho 2 đối tượng có giao hay cắt nhau không nên khiến cho việc va chạm chưa đẹp mắt
   + Thuật toán giúp lớp Threat thay đổi hướng bắn được viết dựa theo cơ chế khoảng cách theo trục x của tọa độ Đề các. Khi tọa độ x của người chơi lớn hơn tọa độ x của Threat thì chúng sẽ bắn sang phải, nếu tọa độ x của người chơi nhỏ hơn thì chúng sẽ bắn sang trái. Tuy nhiên nếu 2 tọa độ X này bằng nhau thì sẽ khiến Threat không xác định được phương hướng từ đó nó sẽ bắn loạn xạ trái phải. Tuy nhiên, nếu ta thêm điều kiện về tọa độ Y thì vẫn còn trường hợp không thỏa mãn. Em hi vọng các thầy có thể sửa chữa và góp ý để kĩ năng lập trình của em được hoàn thiện hơn (hàm kiểm tra hướng bắn là MakeBullet() trong file Threats.cpp)










