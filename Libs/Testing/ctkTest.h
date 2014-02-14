/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// Qt includes
#include <QtTest/QtTest>

#define CTK_TEST_NOOP_MAIN(TestObject) \
int TestObject(int argc, char *argv[]) \
{ \
    QObject tc; \
    return QTest::qExec(&tc, argc, argv); \
}

#ifdef QT_GUI_LIB

//-----------------------------------------------------------------------------
#define CTK_TEST_MAIN(TestObject) \
  int TestObject(int argc, char *argv[]) \
  { \
    QApplication app(argc, argv); \
    TestObject##er tc; \
    return QTest::qExec(&tc, argc, argv); \
  }

#else

//-----------------------------------------------------------------------------
#define CTK_TEST_MAIN(TestObject) \
  int TestObject(int argc, char *argv[]) \
  { \
    QCoreApplication app(argc, argv); \
    QTEST_DISABLE_KEYPAD_NAVIGATION \
    TestObject##er tc; \
    return QTest::qExec(&tc, argc, argv); \
  }

#endif // QT_GUI_LIB

namespace ctkTest
{
static void mouseEvent(QTest::MouseAction action, QWidget *widget, Qt::MouseButton button,
                       Qt::KeyboardModifiers stateKey, QPoint pos, int delay=-1)
{
  if (action != QTest::MouseMove)
    {
    QTest::mouseEvent(action, widget, button, stateKey, pos, delay);
    return;
    }
  QTEST_ASSERT(widget);
  //extern int Q_TESTLIB_EXPORT defaultMouseDelay();
  //if (delay == -1 || delay < defaultMouseDelay())
  //    delay = defaultMouseDelay();
  if (delay > 0)
      QTest::qWait(delay);

  if (pos.isNull())
      pos = widget->rect().center();

  QTEST_ASSERT(button == Qt::NoButton || button & Qt::MouseButtonMask);
  QTEST_ASSERT(stateKey == 0 || stateKey & Qt::KeyboardModifierMask);

  stateKey &= static_cast<unsigned int>(Qt::KeyboardModifierMask);

  QMouseEvent me(QEvent::User, QPoint(), Qt::LeftButton, button, stateKey);

  me = QMouseEvent(QEvent::MouseMove, pos, widget->mapToGlobal(pos), button, button, stateKey);
  QSpontaneKeyEvent::setSpontaneous(&me);
  if (!qApp->notify(widget, &me))
    {
    static const char *mouseActionNames[] =
        { "MousePress", "MouseRelease", "MouseClick", "MouseDClick", "MouseMove" };
    QString warning = QString::fromLatin1("Mouse event \"%1\" not accepted by receiving widget");
    QTest::qWarn(warning.arg(QString::fromLatin1(mouseActionNames[static_cast<int>(action)])).toAscii().data());
    }
}

inline void mouseMove(QWidget *widget, Qt::MouseButton button, Qt::KeyboardModifiers stateKey = 0,
                      QPoint pos = QPoint(), int delay=-1)
  { ctkTest::mouseEvent(QTest::MouseMove, widget, button, stateKey, pos, delay); }

}
