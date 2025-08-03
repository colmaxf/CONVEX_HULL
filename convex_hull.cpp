#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <iomanip>

// Định nghĩa một cấu trúc để lưu trữ một điểm 2D
struct Point {
    double x, y;
};


/**
 * @brief Hàm tạo tệp dữ liệu gòm các điểm tọa độ Oxy
 * @param NUM_COORDINATES Số lượng cặp tọa độ bạn muốn tạo
 * @param MIN_VAL Giá trị nhỏ nhất cho tọa độ
 * @param MAX_VAL Giá trị lớn nhất cho tọa độ
 */
void coordinates(int NUM_COORDINATES, double MIN_VAL, double MAX_VAL)
{
     // --- CÁC THAM SỐ CÓ THỂ ĐIỀU CHỈNH ---
    // const int NUM_COORDINATES = 10; // Số lượng cặp tọa độ bạn muốn tạo
    // const double MIN_VAL = -10.0;     // Giá trị nhỏ nhất cho tọa độ
    // const double MAX_VAL = 10.0;    // Giá trị lớn nhất cho tọa độ
    // ------------------------------------

    // 1. Thiết lập bộ tạo số ngẫu nhiên
    std::random_device rd;  // Nguồn entropy thực sự (nếu có)
    std::mt19937 gen(rd()); // Mersenne Twister engine, được khởi tạo với rd
    std::uniform_real_distribution<> distr(MIN_VAL, MAX_VAL); // Phân phối đều trong khoảng [MIN_VAL, MAX_VAL]

    // 2. Mở file để ghi
    std::ofstream outFile("coordinates.txt");

    // Kiểm tra xem file có mở thành công không
    if (!outFile.is_open()) {
        std::cerr << "erro: can't open file." << std::endl;
        return ; 
    }

    std::cout << "Processing... " << NUM_COORDINATES << " coordinates and save as file coordinates.txt..." << std::endl;

    // 3. Vòng lặp để tạo và ghi tọa độ
    for (int i = 0; i < NUM_COORDINATES; ++i) {
        double x = distr(gen); // Tạo tọa độ x ngẫu nhiên
        double y = distr(gen); // Tạo tọa độ y ngẫu nhiên

        // Ghi cặp tọa độ vào file, định dạng 1 chữ số thập phân
        outFile << std::fixed << std::setprecision(1) << x << " " << y << std::endl;
    }

    outFile.close();

    std::cout << "Create file coordinates.txt successfully." << std::endl;
}

/**
 * @brief Trộn hai mảng con đã sắp xếp của arr.
 * Mảng con thứ nhất là arr[left..mid], mảng con thứ hai là arr[mid+1..right].
 */
void merge(std::vector<Point>& arr, int left, int mid, int right) {
    int const subArrayOne = mid - left + 1; // Kích thước của mảng con thứ nhất
    int const subArrayTwo = right - mid;    // Kích thước của mảng con thứ hai

    // Tạo các vector tạm thời để lưu hai mảng con
    std::vector<Point> leftArray(subArrayOne);
    std::vector<Point> rightArray(subArrayTwo);

    // Sao chép dữ liệu từ mảng chính vào các mảng tạm
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    // Khởi tạo các chỉ số cho việc trộn
    auto indexOfSubArrayOne = 0; // Chỉ số cho mảng con trái
    auto indexOfSubArrayTwo = 0; // Chỉ số cho mảng con phải
    int indexOfMergedArray = left; // Chỉ số để ghi vào mảng chính, bắt đầu từ 'left'

    // Vòng lặp để trộn hai mảng con vào mảng chính
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        // Logic so sánh: ưu tiên tọa độ x, nếu x bằng nhau thì xét đến y
        if (leftArray[indexOfSubArrayOne].x < rightArray[indexOfSubArrayTwo].x ||
           (leftArray[indexOfSubArrayOne].x == rightArray[indexOfSubArrayTwo].x &&
            leftArray[indexOfSubArrayOne].y <= rightArray[indexOfSubArrayTwo].y)) {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne]; // Lấy phần tử từ mảng trái
            indexOfSubArrayOne++; // Tăng chỉ số mảng trái
        } else {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo]; // Lấy phần tử từ mảng phải
            indexOfSubArrayTwo++; // Tăng chỉ số mảng phải
        }
        indexOfMergedArray++; // Tăng chỉ số của mảng chính
    }

    // Sao chép các phần tử còn lại của mảng trái (nếu có)
    while (indexOfSubArrayOne < subArrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Sao chép các phần tử còn lại của mảng phải (nếu có)
    while (indexOfSubArrayTwo < subArrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

/**
 * @brief Hàm đệ quy để sắp xếp một vector các điểm bằng thuật toán Merge Sort.
 */
void mergeSort(std::vector<Point>& arr, int left, int right) {
    if (left < right) { // Điều kiện dừng đệ quy: khi mảng con chỉ có 1 phần tử
        // Tìm điểm giữa của mảng để chia thành hai nửa. Cách này tránh tràn số khi left, right lớn.
        int mid = left + (right - left) / 2;
        
        // Gọi đệ quy để sắp xếp nửa đầu (từ left đến mid)
        mergeSort(arr, left, mid);
        // Gọi đệ quy để sắp xếp nửa sau (từ mid+1 đến right)
        mergeSort(arr, mid + 1, right);
        
        // Sau khi hai nửa đã được sắp xếp, trộn chúng lại với nhau
        merge(arr, left, mid, right);
    }
}


/**
 * @brief Tính tích có hướng (cross product) của vector (p1, p2) và (p1, p3).
 * @return > 0 nếu là "rẽ trái" (Counter-Clockwise)
 * @return < 0 nếu là "rẽ phải" (Clockwise)
 * @return = 0 nếu 3 điểm thẳng hàng (Collinear)
 */
double cross_product(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

/**
 * @brief Hàm chính để tính toán bao lồi bằng thuật toán Monotone Chain.
 * @param points Vector chứa tất cả các điểm đầu vào.
 * @return Vector chứa các điểm thuộc đường bao lồi.
 */
std::vector<Point> convex_hull(std::vector<Point>& points) {
    int n = points.size();
    if (n <= 2) {
        return points; // Không thể tạo bao lồi với ít hơn 3 điểm
    }

    // 1. Sắp xếp các điểm
    mergeSort(points, 0, n - 1);

    std::vector<Point> lower_hull;
    std::vector<Point> upper_hull;

    // 2. Xây dựng bao dưới (lower hull)
    for (const auto& p : points) {
        while (lower_hull.size() >= 2 && cross_product(lower_hull[lower_hull.size()-2], lower_hull.back(), p) <= 0) {
            lower_hull.pop_back(); // Loại bỏ điểm cuối nếu rẽ phải hoặc thẳng hàng
        }
        lower_hull.push_back(p);
    }

    // 3. Xây dựng bao trên (upper hull)
    for (int i = n - 1; i >= 0; --i) {
        Point p = points[i];
         while (upper_hull.size() >= 2 && cross_product(upper_hull[upper_hull.size()-2], upper_hull.back(), p) <= 0) {
            upper_hull.pop_back(); // Loại bỏ điểm cuối
        }
        upper_hull.push_back(p);
    }
    
    // 4. Kết hợp hai nửa bao lồi
    // Nối bao trên vào bao dưới, bỏ qua điểm đầu và cuối của bao trên vì chúng trùng với bao dưới
    for (size_t i = 1; i < upper_hull.size() - 1; i++) {
        lower_hull.push_back(upper_hull[i]);
    }

    return lower_hull;
}

int main(int argc, char* argv[]) {
    // argc: đếm số lượng tham số (luôn >= 1)
    // argv: mảng các chuỗi chứa tham số

    // Kiểm tra đã nhập đủ tham số chưa
    if (argc != 4) {
        std::cerr << "Error: Invalid syntax!" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <quantity> <min_value> <max_value>" << std::endl;
        std::cerr << "Example: " << argv[0] << " 10 -10.0 10.0" << std::endl;
        return 0; 
    }

    try {
        // Chuyển đổi tham số từ chuỗi (string) sang số (number)
        int num_coordinates = std::stoi(argv[1]);
        double min_val = std::stod(argv[2]);
        double max_val = std::stod(argv[3]);

        // Kiểm tra logic đơn giản
        if (min_val > max_val) {
            std::cerr << "Error: Min value cannot be greater than max value." << std::endl;
            return 0;
        }
 
        //Tạo các tọa độ Oxy random
        coordinates(num_coordinates, min_val, max_val);

        // Đọc file coordinates.txt
        std::ifstream inputFile("coordinates.txt");
        if (!inputFile) {
            std::cerr << "erro: can't open file points.txt" << std::endl;
            return 0;
        }

        std::vector<Point> points;
        Point p;
        while (inputFile >> p.x >> p.y) {
            points.push_back(p);
        }
        inputFile.close();

        std::cout << "Read file points.txt successfully: " << points.size() << std::endl;
        for (int i = 0; i < points.size(); i++)
        {
            std::cout << "(" << points[i].x << ", " << points[i].y << ")" << std::endl;
        }
        

        // Tính toán bao lồi
        std::vector<Point> hull = convex_hull(points);

        // In kết quả
        std::cout << "\nConvex Hull: " << std::endl;
        for (const auto& hull_point : hull) {
            std::cout << "(" << hull_point.x << ", " << hull_point.y << ")" << std::endl;
        }

        // Lưu kết quả ra file
        std::ofstream outputFile("hull_output.txt");
        for (const auto& hull_point : hull) {
            outputFile << hull_point.x << " " << hull_point.y << std::endl;
        }
        // Nối điểm cuối với điểm đầu để đa giác được khép kín khi vẽ
        if (!hull.empty()) {
             outputFile << hull[0].x << " " << hull[0].y << std::endl;
        }
        outputFile.close();
        std::cout << "\nCpmpelte successfully" << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid parameter. Please enter a number." << std::endl;
        return 0;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Parameter out of range." << std::endl;
        return 0;
    }

    return 0;
}