#include "CppUnitTest.h"
#include "..\ProgrammingMethods_LR1_oop\aphorism.h"
#include "..\ProgrammingMethods_LR1_oop\container.h"
#include "..\ProgrammingMethods_LR1_oop\node.h"
#include "..\ProgrammingMethods_LR1_oop\phrase.h"
#include "..\ProgrammingMethods_LR1_oop\proverb.h"
#include "..\ProgrammingMethods_LR1_oop\riddle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace type_phrases;

namespace UnitTestsForOOP
{
	TEST_CLASS(UnitTestsForLab3)
	{
	public:
		// Тест функции container_Fill()
		TEST_METHOD(TestInputContainerWithElem)
		{
			ifstream ifst("InputContainer4.txt"); // 4 элемента
			container c;
			c.container_Fill(ifst);
			ifst.close();

			ifstream input_file("InputContainer4.txt");
			string s;
			int real_len = 0;
			while (input_file.peek() != EOF) {
				getline(input_file, s);
				real_len++;
			}
			input_file.close();

			Assert::AreEqual(c.get_Size(), real_len / 4);
			c.container_Clear();
		}
		// Тест функции container_Fill()
		TEST_METHOD(TestInputContainerEmpty)
		{
			ifstream ifst("InputContainer0.txt"); // 0 элемента
			container c;
			c.container_Fill(ifst);
			ifst.close();

			Assert::AreEqual(c.get_Size(), 0);
			c.container_Clear();
		}


		// Тест функции container_Clear()
		TEST_METHOD(ContainerClean0)
		{
			ifstream ifst("InputContainer0.txt"); // 0 элементов
			container c;
			c.container_Fill(ifst);
			c.container_Clear();
			ifst.close();

			Assert::AreEqual(c.get_Size(), 0);
		}
		// Тест функции container_Clear()
		TEST_METHOD(ContainerCleanWithElem)
		{
			ifstream ifst("InputContainer4.txt"); // 4 элементов
			container c;
			c.container_Fill(ifst);
			int size = c.get_Size();
			c.container_Clear();
			ifst.close();

			Assert::AreEqual(c.get_Size(), 0);
		}


		// Тест функции container_Output()
		TEST_METHOD(TestOutputContainerWithElem)
		{
			ifstream ifst("InputContainer4.txt"); // 4 элемента
			ofstream ofst("OutputContainer4.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream pattern("PatternOutputContainer4.txt");
			ifstream current("OutputContainer4.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual(res+1,0);			
		}


		// Тест функции phrase_Input() на корректность ключа
		TEST_METHOD(PhraseInputWithElem)
		{
			ifstream ifst("InputPhraseIncorrectKey.txt"); //В файле 8 мудростей, 4 из которых с некорректными ключами
			ofstream ofst("OutputPhraseIncorrectKey.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream pattern("PatternOutputPhraseIncorrectKey.txt");
			ifstream current("OutputPhraseIncorrectKey.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual(res + 1, 0);
		}
		// Проверка поведения в случае неверного формата ввода (отсутствует строка Type of wisdom)
		TEST_METHOD(PhraseInputWithoutKey)
		{
			ifstream ifst("InputPhraseNoKey.txt"); // В файле 2 мудрости, одна из которых без Type of wisdom
			container c;
			c.container_Fill(ifst);
			ifst.close();

			Assert::AreEqual(c.get_Size(), 0);
			c.container_Clear();
		}
		// Проверка поведения в случае неожидаемого формата ввода (поля типа string сдвинуты)
		TEST_METHOD(PhraseInputUnexpectedFields)
		{
			ifstream ifst("InputPhraseUnexpectedFields.txt"); // В файле 1 мудрость со сдвинутыми полями
			container c;
			c.container_Fill(ifst);
			ifst.close();

			Assert::AreEqual(c.get_Size(), 1);
			c.container_Clear();
		}
		// Проверка поведения при наличии пустых строк между фразами
		TEST_METHOD(PhraseInputEmptyLines)
		{
			ifstream ifst("InputPhraseEmptyLines.txt"); //В файле 4 мудрости с пустыми строками между ними
			container c;
			c.container_Fill(ifst);
			ifst.close();

			Assert::AreEqual(c.get_Size(), 1);
			c.container_Clear();
		}


		// Тест функции sort()
		TEST_METHOD(ContainerSortWithElem)
		{
			ifstream ifst("InputContainer4.txt"); // 4 элемента
			ofstream ofst("OutputSortCont4.txt");
			container c;
			c.container_Fill(ifst);
			c.sort();
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();
			
			ifstream pattern("PatternOutputSortCont4.txt");
			ifstream current("OutputSortCont4.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual((res + 1), 0);
		}
		// Тест функции sort() для пустого контейнера
		TEST_METHOD(ContainerSortWithoutElem)
		{
			ifstream ifst("InputContainer0.txt"); // В файле пусто
			ofstream ofst("OutputSortCont0.txt");
			container c;
			c.container_Fill(ifst);
			c.sort();
			c.container_Output(ofst);
			ifst.close();
			ofst.close();

			Assert::AreEqual(c.get_Size(), 0);
			c.container_Clear();
		}
		// Тест функции sort() для контейнера с одним элементом
		TEST_METHOD(ContainerSortOneElem)
		{
			ifstream ifst("InputContainer1.txt"); // В файле один элемент
			ofstream ofst("OutputSortCont1.txt");
			container c;
			c.container_Fill(ifst);
			c.sort();
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream pattern("PatternOutputSortCont1.txt");
			ifstream current("OutputSortCont1.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual((res + 1), 0);
		}
		// Тест функции sort() для контейнера с двумя элементами
		TEST_METHOD(ContainerSortTwoElem)
		{
			ifstream ifst("InputContainer2.txt"); // В файле два элемента
			ofstream ofst("OutputSortCont2.txt");
			container c;
			c.container_Fill(ifst);
			c.sort();
			c.container_Output(ofst);
			//c.container_Clear();
			ifst.close();
			ofst.close();

			/*ifstream pattern("PatternOutputSortCont2.txt");
			ifstream current("OutputSortCont2.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual((res + 1), 0);*/

			ifstream input_file("InputContainer2.txt");
			string s;
			int real_len = 0;
			while (input_file.peek() != EOF) {
				getline(input_file, s);
				real_len++;
			}
			input_file.close();

			Assert::AreEqual(c.get_Size(), real_len / 4);
			c.container_Clear();
		}


		// Тест функции aphorism_Out() для пустого контейнера
		TEST_METHOD(OutputOnlyAphorismsFromEmptyCont)
		{
			ifstream ifst("InputContainer0.txt"); // В файле пусто
			ofstream ofst("OutputOnlyAphorism0.txt");
			container c;
			c.container_Fill(ifst);
			c.container_OutputAphos(ofst); // В выходном файле "Only aphorisms"
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream input_file("OutputOnlyAphorism0.txt");
			string s;
			int real_len = 0;
			while (input_file.peek() != EOF) {
				getline(input_file, s);
				real_len++;
			}
			input_file.close();

			Assert::AreEqual((real_len - 1) / 4, 0);
		}
		// Тест функции aphorism_Out() без афоризмов в контейнере
		TEST_METHOD(OutputAphorismsFromContWithoutAphors)
		{
			ifstream ifst("InputContWithoutAphos.txt"); //В файле 2 мудрости
			ofstream ofst("OutputContWithoutAphos.txt");
			container c;
			c.container_Fill(ifst);
			c.container_OutputAphos(ofst); // В выходном файле "Only aphorisms"
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream input_file("OutputContWithoutAphos.txt");
			string s;
			int real_len = 0;
			while (input_file.peek() != EOF) {
				getline(input_file, s);
				real_len++;
			}
			input_file.close();

			Assert::AreEqual((real_len - 1) / 4, 0);
		}


		// Проверка функции num_punct_marks() в случае отсутсвия знаков препинания
		/*TEST_METHOD(NumPunctMarks0)
		{
			ifstream ifst("InputPhrasePunctMarks0.txt"); // В выражении нет запятых
			ofstream ofst("OutputPhrasePunctMarks0.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream input_file("OutputPhrasePunctMarks0.txt");
			string s;
			while (input_file.peek() != EOF) {
				getline(input_file, s);
			}
			input_file.close();
			s = s[s.length() - 2];

			Assert::AreEqual(atoi(s.c_str()), 0);
		}*/
		// Проверка функции num_punct_marks() в случае 1 знака препинания
		TEST_METHOD(NumPunctMarks1)
		{
			ifstream ifst("InputContainer1.txt"); //В выражении 1 запятая
			ofstream ofst("OutputPhrasePunctMarks1.txt");
			phrase* info = phrase::phrase_Input(ifst);;
			ofst << "Number of punctuation marks: " << info->num_punct_marks() << "." << endl;
			ifst.close();
			ofst.close();

			ifstream pattern("PatternOutputPhrasePunctMarks1.txt");
			ifstream current("OutputPhrasePunctMarks1.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual((res + 1), 0);
		}
		// Проверка функции num_punct_marks() в случае 4 знаков препинания
		TEST_METHOD(NumPunctMarks4)
		{
			ifstream ifst("InputPhrasePunctMarks4.txt"); //В выражении 4 знака препинания
			ofstream ofst("OutputPhrasePunctMarks4.txt");
			phrase* info = phrase::phrase_Input(ifst);;
			ofst << "Number of punctuation marks: " << info->num_punct_marks() << "." << endl;
			ifst.close();
			ofst.close();

			ifstream pattern("PatternOutputPhrasePunctMarks4.txt");
			ifstream current("OutputPhrasePunctMarks4.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual((res + 1), 0);
		}


		// Тест функций aphorism_Output()
		/*TEST_METHOD(TestOutputAphorism)
		{
			ifstream ifst("InputAphorism.txt");
			ofstream ofst("OutputAphorism.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream pattern("PatternOutputAphorism.txt");
			ifstream current("OutputAphorism.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual((res + 1), 0);
		}*/
		// Тест функции proverb_Output()
		TEST_METHOD(TestOutputProverb)
		{
			ifstream ifst("InputProverb.txt");
			ofstream ofst("OutputProverb.txt");
			phrase* info = phrase::phrase_Input(ifst);
			info->Output(ofst);
			info->phrase_Output(ofst);
			ifst.close();
			ofst.close();

			ifstream pattern("PatternOutputProverb.txt");
			ifstream current("OutputProverb.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual((res + 1), 0);
		}
		// Тест функции riddle_Output()
		TEST_METHOD(TestOutputRiddle)
		{
			ifstream ifst("InputRiddle.txt");
			ofstream ofst("OutputRiddle.txt");
			phrase* info = phrase::phrase_Input(ifst);
			info->Output(ofst);
			info->phrase_Output(ofst);
			ifst.close();
			ofst.close();

			ifstream pattern("PatternOutputRiddle.txt");
			ifstream current("OutputRiddle.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual((res + 1), 0);
		}

		int Compare(ifstream& ifst_1, ifstream& ifst_2)
		{
			char c1;
			char c2;
			int pos = -1;
			while (ifst_1.get(c1) && ifst_2.get(c2)) {
				pos++;
				if (c1 != c2)
				{
					return pos;
				}
			}
			return -1;
		}

	};
}
