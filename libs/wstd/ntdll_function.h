/** \file ntdll_function.h
 Заголовочный файл описывает недокументированные функции NTDLL WINAPI.
*/

#ifndef NTDLL_FUNCTION_H
#define NTDLL_FUNCTION_H

#include <Windows.h>

#pragma comment(lib, "ntdll")

/**
 \brief Функция возвращает разрешение системного таймера в контексте 
        вызывающего процесса.

 Недокументированная функция NTDLL WINAPI.

 \param [out] MinimumResolution - Возвращает максимально возможную задержку
                                  (начиная со 100 нс) между событиями таймера.
 \param [out] MaximumResolution - Возвращает минимально возможную задержку
                                  (начиная со 100 нс) между событиями таймера.
 \param [out] CurrentResolution - Текущее разрешение таймера начиная со 100 нс.
*/
extern "C" NTSYSAPI NTSTATUS NTAPI NtQueryTimerResolution(
	PULONG MinimumResolution, PULONG MaximumResolution, PULONG CurrentResolution);


/**
 \brief Функция устанавливает разрешение системного таймера в контексте
        вызывающего процесса.

 Недокументированная функция NTDLL WINAPI.

 \param [in] DesiredResolution - Устанавливает разрешение таймера. Чтобы 
                                 получить минимальное и максимальное разрешение 
                                 таймера вызовите NtQueryTimerResolution.
 \param [in] SetResolution - Если true - разрешение системного таймера 
                             устанавливается равным значению DesiredResolution, 
                             если false - параметр DesiredResolution игнорируется.
 \param [out] CurrentResolution - Текущее разрешение таймера начиная со 100 нс.
*/
extern "C" NTSYSAPI NTSTATUS NTAPI NtSetTimerResolution(
	ULONG DesiredResolution, BOOLEAN SetResolution, PULONG CurrentResolution);


/**
 \brief Функция реализует таймер ожидания.

 Недокументированная функция NTDLL WINAPI.

 \param [in] Alertable - Указывает значение TRUE, если ожидание является
                         предупреждающим. Драйверы более низкого уровня
                         должны указывать значение FALSE.
 \param [in] DelayInterval - Указывает абсолютное или относительное время 
                             в единицах измерения 100 наносекунд, в течении 
                             которого должно произойти ожидание. Отрицательное 
                             значение указывает относительное время. Абсолютное 
                             время истечения отслеживает любые изменения 
                             системного времени; изменения системного времени 
                             не влияют на относительное время истечения.
*/
extern "C" NTSYSCALLAPI NTSTATUS NTAPI NtDelayExecution(
	BOOLEAN Alertable, PLARGE_INTEGER DelayInterval);

#endif //NTDLL_FUNCTION_H