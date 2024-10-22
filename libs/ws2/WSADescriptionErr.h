#ifndef WSADESCRIPTIONERR_H
#define WSADESCRIPTIONERR_H

#include <string>

namespace ws2 {

  /** \class WSADescriptionErr
   \brief Структура предназначена для расшифровки кода ошибки
          WSAGetLastError().
  */
  class WSADescriptionErr {
  public:
    struct Description_t {
      std::string name;
      std::string descr;

      Description_t() : name("No name"), descr("Unknown error") {}
    }; //struct Description

    /**
     \brief Конструктор по умолчанию.
     \param[in] errorCode - Код ошибки.
    */
    WSADescriptionErr(int code = 0);

    /**
     \brief Метод возвращает код ошибки WSA.
     \return Код ошибки WSA.
    */
    int Code() const;

    /**
      \brief Метод возвращает структуру с текстовым описанием ошибки.
      \return Структура с текстовым описанием ошибки.
    */
    Description_t Description() const;

    /**
     \brief Метод возвращает название ошибки из перечня WSA.
     \return Наименование ошибки (например: "WSANOTINITIALISED").
    */
    std::string Name() const;

    /**
     \brief Метод возвращает текстовое описание ошибки.
     \return Текстовое описание ошибки.
    */
    std::string Descr() const;

    /**
     \brief Метод возвращает полное текстовое описание ошибки.
     \return Код ошибки + Имя ошибки + Описание ошибки.
    */
    std::string GetFullDescr() const;

    /**
     \brief Метод возвращает полное текстовое описание ошибки с заголовком.
     \return Заголовок + Код ошибки + Имя ошибки + Описание ошибки.
    */
    std::string GetFullDescr(std::string prescript) const;

  private:
    int _code;  //!< Код ошибки.

  };//class WSADescriptionErr

}//namepace ws2

#endif //WSADESCRIPTIONERR_H