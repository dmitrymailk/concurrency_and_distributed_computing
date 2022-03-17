/*
Архитектура и операционные системы параллельных вычислительных систем А.В. Кудин, А.В. Линёв
СТР 55
TODO Задача «Производители-потребители»

Одной из типовых задач, требующих синхронизации, является задача producer-consumer problem
(производитель-потребитель). Пусть два потока обмениваются информацией
через буфер ограниченного размера. Производитель добавляет информацию в буфер, а
потребитель извлекает ее оттуда

Сразу необходимо отметить, что если буфер пуст, то потребитель должен ждать,
пока в нем появятся данные, а если буфер полон, то производитель должен ждать
появления свободного элемента. В данном случае реализация производителя и
потребителя будет иметь следующий вид.

Producer:
while (true)
{
	PrepareData();	   // Подготовить данные
	while (!Put(Data)) // Разместить данные
		;
}

Consumer:
while (true)
{
	while (!Get(&Data)); // Считать данные

	UseData(); // Использовать данные
}

Задача «Производители-Потребители» заключается в обеспечении согласованного
доступа нескольких потоков к разделяемому циклическому буферу. Корректное
решение должно удовлетворять следующим условиям:
- потоки выполняются параллельно;
- одновременно в критической секции, связанной с каждым критическим ресурсом,
должно находиться не более одного потока;
- потоки должны завершить работу в течение конечного времени;
- потоки должны корректно использовать операции с циклическим буфером.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NITER 10

// Function prototypes
void producer();
void consumer();

// Shared by the producer and consumer thread
int buffer[BUFFER_SIZE];
int in = 0;	 // next free position
int out = 0; // first full position

int main()
{
	srand(time(NULL));

#pragma omp parallel sections
	{
#pragma omp section
		producer();

#pragma omp section
		consumer();
	}

	return 0;
}

void producer()
{
	int next_produced;
	// while (1){
	for (int i = 0; i < NITER; i++)
	{
		next_produced = rand() % 100 + 1;

		// Do nothing until a slot is available
		while (((in + 1) % BUFFER_SIZE) == out)
			;

		buffer[in] = next_produced;
		printf("Producer produced [%d].(Placed in index:in=%d,out=%d)\n", next_produced, in, out);
		in = (in + 1) % BUFFER_SIZE;
	}
}

void consumer()
{
	int next_consumed;
	// while(1){
	for (int i = 0; i < NITER; i++)
	{

		// Do nothing if the buffer is empty
		while (in == out)
			;

		next_consumed = buffer[out];
		printf("=Consumer consumed [%d].(in=%d,Consumed from index: out=%d)\n", next_consumed, in, out);
		out = (out + 1) % BUFFER_SIZE;
	}
}
