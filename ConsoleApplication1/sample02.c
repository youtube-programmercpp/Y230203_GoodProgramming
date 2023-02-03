#define	_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h> //exit 関数用
#include <stdbool.h> //C++ では不要
#define N 3
struct reader* reader_new();
void reader_delete(struct reader* reader);
bool reader_can_read(const struct reader* this);
int reader_read_data(struct reader* this);
int main() {
	struct reader* const reader = reader_new();
	int count = 0;
	while (reader_can_read(reader)) {
		if (!(reader_read_data(reader) & 1))
			++count;
	}
	printf("個数: %d\n", count);
	reader_delete(reader);
}

// DLL dynamic link library

struct reader {
	FILE* fp;
	int i;//読み込み済みのデータ個数
	//メンバを後で追加しても大丈夫
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
struct reader* reader_new()
{
	struct reader* const p = malloc(sizeof * p);
	if (p) {
		//メモリ割り付け成功
		reader_construct(p);
		return p;
	}
	else {
		//メモリ割り付け失敗
		fprintf(stderr, "malloc 関数が失敗しました。\n");
		exit(EXIT_FAILURE);
	}
}
//作成されたオブジェクトを破棄する
void reader_destruct(struct reader* this)
{
	if (this->fp)
		fclose(this->fp);
}
void reader_delete(struct reader* reader)
{
	if (reader) {
		reader_destruct(reader);//オブジェクト破棄
		free(reader);//メモリ解放
	}
}

//データ読み込み可否判断
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
