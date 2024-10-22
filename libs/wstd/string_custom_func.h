#ifndef STRING_CUSTOM_FUNC_H
#define STRING_CUSTOM_FUNC_H

#include <algorithm>
#include <cctype>
#include <stdexcept>

//#define NOMINMAX  // Убирает конфликт между min max из winAPI и библиотеки STL.
#include <windows.h>

namespace wstd {

/** \class Utf8ConversionExeption
 \brief Представляет ошибку при преобразованиях кодировки UTF-8.
*/
class Utf8ConversionExeption : public std::runtime_error
{
public:
	/**
	 \brief Конструктор.

	 \param[in] message - Описание ошибки.
	 \param[in] errorCode - Код ошибки.
	*/
	Utf8ConversionExeption(const char* message, uint32_t errorCode)
		: std::runtime_error(message), _errorCode(errorCode)
	{ }//--------------------------------------------------------------

	/**
	 \brief Метод возвращает код ошибки полученный из GetLastError().

	 \return Код ошибки.
	*/
	uint32_t ErrorCode() const {
		return _errorCode;
	}//----------------------------------------------------------------

private:
	uint32_t _errorCode;  //!< Код ошибки от GetLastError()

}; //class Utf8ConversionExeption
//-------------------------------------------------------------------


/**
 \brief Функция удаляет пробел из начала переданной на обработку строки.
 \param [in,out] s - Ссылка на строку для обработки.
*/
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), 
		[](unsigned char ch) { return !std::isspace(ch); })
	);
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел из начала переданной на обработку строки.
 \param [in,out] s - Ссылка на строку для обработки.
*/
static inline void ltrim(std::wstring& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), 
		[](wchar_t ch) { return !std::isspace(ch); })
	);
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел в конце переданной на обработку строки.
 \param [in,out] s - Ссылка на строку для обработки.
*/
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел в конце переданной на обработку строки.
 \param [in,out] s - Ссылка на строку для обработки.
*/
static inline void rtrim(std::wstring& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](wchar_t ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел и в начале, и в конце переданной
        на обработку строки.

 \param [in,out] s - Ссылка на строку для обработки.
*/
static inline void trim(std::string& s) {
	rtrim(s);
	ltrim(s);
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел и в начале, и в конце переданной
 на обработку строки.

 \param [in,out] s - Ссылка на строку для обработки.
*/
static inline void trim(std::wstring& s) {
	rtrim(s);
	ltrim(s);
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел из начала переданной на обработку 
        строки и возвращает изменённый вариант.
 \param [in] s - Строка для обработки.
 \return Изменённая строка.
*/
static inline std::string ltrim_copy(std::string s) {
	ltrim(s);
	return s;
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел из начала переданной на обработку 
        строки и возвращает изменённый вариант.
 \param [in] s - Строка для обработки.
 \return Изменённая строка.
*/
static inline std::wstring ltrim_copy(std::wstring s) {
	ltrim(s);
	return s;
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел в конце переданной на обработку 
        строки и возвращает изменённый вариант.
 \param [in] s - Строка для обработки.
 \return Изменённая строка.
*/
static inline std::string rtrim_copy(std::string s) {
	rtrim(s);
	return s;
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел в конце переданной на обработку строки
        и возвращает изменённый вариант.
 \param [in] s - Строка для обработки.
 \return Изменённая строка.
*/
static inline std::wstring rtrim_copy(std::wstring s) {
	rtrim(s);
	return s;
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел и в начале, и в конце переданной 
        на обработку строки и возвращает изменённый вариант.
 \param [in] s - Строка для обработки.
 \return Изменённая строка.
*/
static inline std::string trim_copy(std::string s) {
	trim(s);
	return s;
}//------------------------------------------------------------------


/**
 \brief Функция удаляет пробел и в начале, и в конце переданной 
        на обработку строки и возвращает изменённый вариант.
 \param [in] s - Строка для обработки.
 \return Изменённая строка.
*/
static inline std::wstring trim_copy(std::wstring s) {
	trim(s);
	return s;
}//------------------------------------------------------------------


/**
 \brief Функция сравнивает две строки (без учёта регистра).

 Функция выполняет сравнение двух переданных строк без учёта регистра.
 Операция сравнения управляется текущим языковым стандартом Windows.

 \TODO Можно реализовать с помощью boost::iequals

 \param [in] s1 - Первая строка для сравнения.
 \param [in] s2 - Вторая строка для сравнения.
 \return Количество несовпадающих символов:
    | Состояние | Возвращаемое значение |
    | :-------: | :-------------------- |
    |  s1 > s2  | >0                    |
    |  s1 < s2  | <0                    |
    |  s1 = s2  | =0                    |
*/
static inline int string_compare_IC(std::string s1, std::string s2) {
	std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
	std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
	return s1.compare(s2);
}//------------------------------------------------------------------


/**
 \brief Функция сравнивает две строки (без учёта регистра).

 Функция выполняет сравнение двух переданных строк без учёта регистра.
 Операция сравнения управляется текущим языковым стандартом Windows.

 \TODO Можно реализовать с помощью boost::iequals

 \param [in] s1 - Первая строка для сравнения.
 \param [in] s2 - Вторая строка для сравнения.
 \return Количество несовпадающих символов:
    | Состояние | Возвращаемое значение |
    | :-------: | :-------------------- |
    |  s1 > s2  | >0                    |
    |  s1 < s2  | <0                    |
    |  s1 = s2  | =0                    |
*/
static inline int string_compare_IC(std::wstring s1, std::wstring s2) {
	std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
	std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
	return s1.compare(s2);
}//------------------------------------------------------------------


/**
 \brief Конвертирует C++ string в WINDOWS UNICODE wstring.

 \param [in] s - Ссылка на ANSI C++ строку.
 \exception std::exception - Входная строка превышает размер буфера.
 \exception Utf8ConversionExeption - Ошибки при конвертировании строки.
 \return Строка в формате WINDOWS UNICODE.
*/
static std::wstring Utf8ToUtf16(const std::string& utf8) {
	if (utf8.empty()) // Если исходная строка пустая, то вернём пустую строку
		return std::wstring{ L"" };

	//Надёжный провал, если во входной строке обнаружился недопустимый символ UTF-8
	//constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;  // Флаг преобразования

	/* Флаг преобразования.  P.S.Флаг MB_ERR_INVALID_CHARS ломает вывод
			при конвертации путей. */
	constexpr DWORD kFlags = 0;

	/* Проверка того, что длина size_t не превысит максимальное значение
			для переменной типа int. */
	if (utf8.length() > static_cast<size_t>((
		std::numeric_limits<int>::max)()))
	{
		throw std::exception(
			"Utf8ToUtf16() Input string too long: size_t-length doesn't fit into int.");
	}

	/* Безопасное преобразование из size_t(длина STL - строки)
			в int(для Win32 - функций). */
			// Длина строки UTF-8.
	const int utf8Length = static_cast<int>(utf8.length());

	/* Вызываем MultiByteToWideChar в первый раз чтобы получить длину
			конечной строки UTF-16 */
	const int utf16Length = ::MultiByteToWideChar( //Конечная длина строки UTF-16
		CP_UTF8,      // исходная строка UTF-8
		kFlags,       // флаги преобразования
		utf8.data(),  // указатель на исходную строку UTF-8
		utf8Length,   // длина исходной строки UTF-8 в символах
		nullptr,      // не используется - на этом этапе преобразование не выполняется
		0             // запрос размера буфера назначения в wchar_t
	);

	if (utf16Length == 0) {
		// Ошибка преобразования: захватываем код ошибки и генерируем исключение
		const DWORD error = ::GetLastError();  // Код ошибки
		throw Utf8ConversionExeption(
			"Cannot get result string length when converting " \
			"from UTF-8 to UTF-16 (MultiByteToWideChar failed).",
			error
		);
	}

	std::wstring utf16(L"", utf16Length);  // Формируемая utf16 строка

	/* Вызываем MultiByteToWideChar во второй раз чтобы получить реально
			преобразованные биты в строке назначения */
	int result = ::MultiByteToWideChar(  // Количество обработанных символов
		CP_UTF8,      // исходная строка UTF-8
		kFlags,       // флаги преобразования
		utf8.data(),  // указатель на исходную строку UTF-8
		utf8Length,   // длина исходной строки UTF-8 в символах
		&utf16[0],    // указатель на буфер назначения
		utf16Length   // запрос размера буфера назначения в wchar_t
	);

	if (result == 0) {
		// Ошибка преобразования: захватываем код ошибки и генерируем исключение
		const DWORD error = ::GetLastError();  // Код ошибки
		throw Utf8ConversionExeption(
			"Cannot convert from UTF-8 to UTF-16 " \
			"(MultiByteToWideChar failed).",
			error
		);
	}

	return utf16;
}//------------------------------------------------------------------


/**
 \brief Конвертирует WINDOWS UNICODE wstring в C++ ANSI string.

 \param [in] s - Ссылка на WINDOWS UNICODE строку.
 \exception std::exception - Входная строка превышает размер буфера.
 \exception Utf8ConversionExeption - Ошибки при конвертировании строки.
 \return Строка в формате C++ ANSI.
*/
static std::string Utf16ToUtf8(const std::wstring& utf16) {
	if (utf16.empty()) // Если исходная строка пустая, то вернём пустую строку
		return std::string{ "" };

	//Надёжный провал, если во входной строке обнаружился недопустимый символ UTF-8
	//constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;  // Флаг преобразования

	/* Флаг преобразования  P.S.Флаг MB_ERR_INVALID_CHARS ломает вывод
			при конвертации путей */
	constexpr DWORD kFlags = 0;

	/* Проверка того, что длина size_t не превысит максимальное значение
			для переменной типа int. */
	if (utf16.length() > static_cast<size_t>((
		std::numeric_limits<int>::max)()))
	{
		throw std::exception(
			"Utf8ToUtf16() Input string too long: size_t-length doesn't fit into int.");
	}

	/* Безопасное преобразование из size_t(длина STL - строки)
			в int(для Win32 - функций). */
			// Длина строки UTF-16
	const int utf16Length = static_cast<int>(utf16.length());

	/* Вызываем WideCharToMultiByte в первый раз чтобы получить длину
			конечной строки UTF-16. */
	const int utf8Length = ::WideCharToMultiByte(// Конечная длина строки UTF-16
		CP_UTF8,       // исходная строка UTF-8
		kFlags,        // флаги преобразования
		utf16.data(),  // указатель на исходную строку UTF-16
		utf16Length,   // длина исходной строки UTF-8 в символах
		nullptr,       // не используется - на этом этапе преобразование не выполняется
		0,             // запрос размера буфера назначения в wchar_t
		NULL,          // указатель на символ, используемый, если символ не может быть представлен на указанной кодовой странице
		NULL           // указатель на флаг, указывающий, использовала ли функция символ по умолчанию для преобразования
	);

	if (utf8Length == 0) {
		// Ошибка преобразования: захватываем код ошибки и генерируем исключение
		const DWORD error = ::GetLastError();  // Код ошибки
		throw Utf8ConversionExeption(
			"Cannot get result string length when converting " \
			"from UTF-16 to UTF-8 (WideCharToMultiByte failed).",
			error
		);
	}

	std::string utf8("", utf8Length);  // Формируемая utf8 строка

	/* Вызываем WideCharToMultiByte во второй раз чтобы получить реально
			преобразованные биты в строке назначения */
	int result = ::WideCharToMultiByte(// Количество обработанных символов
		CP_UTF8,       // исходная строка UTF-8
		kFlags,        // флаги преобразования
		utf16.data(),  // указатель на исходную строку UTF-8
		utf16Length,   // длина исходной строки UTF-8 в символах
		&utf8[0],      // указатель на буфер назначения
		utf8Length,    // запрос размера буфера назначения в wchar_t
		NULL,          // указатель на символ, используемый, если символ не может быть представлен на указанной кодовой странице
		NULL           // указатель на флаг, указывающий, использовала ли функция символ по умолчанию для преобразования
	);

	if (result == 0) {
		// Ошибка преобразования: захватываем код ошибки и генерируем исключение
		const DWORD error = ::GetLastError();  // Код ошибки
		throw Utf8ConversionExeption(
			"Cannot convert from UTF-16 to UTF-8 " \
			"(WideCharToMultiByte failed).",
			error
		);
	}

	return utf8;
}//------------------------------------------------------------------

} //namespace wstd

#endif // STRING_CUSTOM_FUNC_H