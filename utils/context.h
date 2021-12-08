#pragma once
#include <mutex>

/*
 * Класс context позволяет управлять работой потоков.
 * Методы класса context являются потокобезопасными.
 * Класс, реализующий интерфейс runnable_actor (см. actors/),
 *  при закрытии контекста должен прекратить работу и закрыть свой поток.
 * Объект класса обязан передавать с помощью указателя для избежания копирования.
 */
class context {
 public:
  /*
   * Конструктор.
   */
  explicit context();
  /*
   * Проверить контекст на закрытие.
   * Потокобезопасный метод.
   * @returns: true, если контекст закрыт.
   */
  bool done();
  /*
   * Закрыть контекст.
   * Потокобезопасный метод.
   */
  void cancel();

 private:
  // Перечисление контекста.
  enum context_state {CONTEXT_ACTIVE, CONTEXT_CANCELED};

  std::mutex ctx_mutex_;
  // Статус контекста.
  context_state ctx_;
};
