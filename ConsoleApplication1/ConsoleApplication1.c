#define	_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h> //exit 関数用
#define N 3
struct reader {
	FILE* fp;
	int i;//読み込み済みのデータ個数
};
//オブジェクトを新規に作る
void reader_construct(struct reader* this)
{
	FILE* const fp = fopen("A.txt", "r");
	if (fp) {
		//成功
		// C99 の compound literal
		*this = (struct reader){ fp, 0 };
	}
	else {
		//失敗
		fprintf(stderr, "fopen 関数が失敗しました。\n");
		exit(EXIT_FAILURE);
	}
}
//作成されたオブジェクトを破棄する
void reader_destruct(struct reader* this)
{
	if (this->fp != NULL)
		fclose(this->fp);
}
//データ読み込み可否判断
#include <stdbool.h> //C++ では不要
bool reader_can_read(const struct reader* this)
{
	return this->i < N;
}
int reader_read_data(struct reader* this)
{
	int x;
	if (fscanf_s(this->fp, "%d", &x) == 1) {
		//成功
		++this->i;
		return x;
	}
	else {
		//失敗
		exit(EXIT_FAILURE);
	}
}
int main() {
	struct reader reader;
	reader_construct(&reader);
	int count = 0;
	while (reader_can_read(&reader)) {
		if (!(reader_read_data(&reader) & 1))
			++count;
	}
	printf("個数: %d\n", count);
	reader_destruct(&reader);
}
