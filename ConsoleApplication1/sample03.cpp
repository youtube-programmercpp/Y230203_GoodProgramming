#include <iostream>
#include <fstream>
#include <stdexcept>//例外
#define N 3
class reader {
	std::ifstream file;
	int i;//読み込み済みのデータ個数
public:
	//オブジェクトを新規に作る
	reader()//コンストラクタ
		: file("B.txt")
		, i (                   )
	{
		if (!file) {
			//失敗
			//例外を投入する
			throw std::runtime_error("fopen 関数が失敗しました。");
		}
	}
	//データ読み込み可否判断
	bool reader_can_read()
	{
		return i < N;
	}
	int reader_read_data()
	{
		int x;
		if (file >> x) {
			//成功
			++i;
			return x;
		}
		else {
			//失敗
			throw std::runtime_error("ファイルからの読み込みに失敗しました。");
		}
	}
};
int main() {
	try {
		reader reader;
		int count = 0;
		while (reader.reader_can_read()) {
			if (!(reader.reader_read_data() & 1))
				++count;
		}
		std::cout << "個数: " << count << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
