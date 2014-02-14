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
#include <QApplication>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QString>
#include <QStyle>
#include <QStyleOptionSlider>
#include <QTimer>

// CTK includes
#include "ctkDoubleSlider.h"
#include "ctkDoubleSpinBox.h"
#include "ctkSliderWidget.h"
#include "ctkTest.h"

// ----------------------------------------------------------------------------
class ctkSliderWidgetTester: public QObject
{
  Q_OBJECT
private slots:
  void testUI();

  void testDecimalsByValue();
  /// This test makes sure the number of decimals increased with Ctrl+'+' does
  /// not break the synchronization between the value of the slider and the
  /// value of the spinbox.
  void testDecimalsByShortcuts();

};

// ----------------------------------------------------------------------------
void ctkSliderWidgetTester::testUI()
{
  ctkSliderWidget slider;
  slider.setMinimum(-100.);
  slider.setMaximum(100.);
  slider.setValue(26.2110001);
  slider.setPrefix("A: ");
  slider.show();
  QTest::qWaitForWindowShown(&slider);
  QObject::connect(&slider, SIGNAL(valueChanged(double)),
                   &slider, SLOT(setValue(double)), Qt::QueuedConnection);


  //qApp->exec();
}

// ----------------------------------------------------------------------------
void ctkSliderWidgetTester::testDecimalsByValue()
{
  ctkSliderWidget slider;
  slider.spinBox()->setDecimalsOption(
    ctkDoubleSpinBox::DecimalsByValue | ctkDoubleSpinBox::DecimalsByShortcuts );
  slider.setValue(-12.4);

  //slider.show();
  //QTest::qWaitForWindowShown(&slider);
  //qApp->exec();
  //QSignalSpy spy(&slider, SIGNAL(decimalsChanged(int)));

  slider.setSingleStep(1.3);
  slider.setRange(-87.2949, 81.7045);
  slider.setValue(-15);

  slider.slider()->triggerAction(QAbstractSlider::SliderSingleStepSub);
  slider.setSingleStep(1.3);
}

// ----------------------------------------------------------------------------
void ctkSliderWidgetTester::testDecimalsByShortcuts()
{
  ctkSliderWidget slider;
  slider.spinBox()->setDecimalsOption(ctkDoubleSpinBox::DecimalsByShortcuts);
  slider.setSingleStep(1.299995422363281);
  slider.setPageStep(1.299995422363281);
  slider.setRange(-100., 100.);
  slider.setValue( -2.145195007324205 );

  slider.show();
  QTest::qWaitForWindowShown(&slider);
  //qApp->exec();
  //QSignalSpy spy(&slider, SIGNAL(decimalsChanged(int)));

  slider.slider()->triggerAction(QAbstractSlider::SliderSingleStepAdd);
  slider.slider()->triggerAction(QAbstractSlider::SliderSingleStepAdd);
  slider.slider()->triggerAction(QAbstractSlider::SliderSingleStepAdd);

  QTest::keyClick(slider.spinBox(), Qt::Key_Plus, Qt::ControlModifier);
  QTest::keyClick(slider.spinBox(), Qt::Key_Plus, Qt::ControlModifier);
  QTest::keyClick(slider.spinBox(), Qt::Key_Plus, Qt::ControlModifier);
  QCOMPARE(slider.decimals(), 5);
}

// ----------------------------------------------------------------------------
CTK_TEST_MAIN(ctkSliderWidgetTest)
#include "moc_ctkSliderWidgetTest.cpp"


