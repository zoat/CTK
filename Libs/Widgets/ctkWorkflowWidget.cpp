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
#include <QDebug>
#include <QWidget>
#include <QWeakPointer>

// CTK includes
#include "ctkWorkflowWidget.h"
#include "ctkWorkflowStep.h"
#include "ctkWorkflowWidgetStep.h"
#include "ctkWorkflow.h"
#include "ctkWorkflowButtonBoxWidget.h"
#include "ctkWorkflowGroupBox.h"
#include "ctkLogger.h"

// STD includes
#include <iostream>

//--------------------------------------------------------------------------
static ctkLogger logger("org.commontk.libs.widgets.ctkWorkflowWidget");
//--------------------------------------------------------------------------

//-----------------------------------------------------------------------------
class ctkWorkflowWidgetPrivate
{
public:
  ctkWorkflowWidgetPrivate();
  ~ctkWorkflowWidgetPrivate();

  QWeakPointer<ctkWorkflow>   Workflow;

  ctkWorkflowGroupBox*        WorkflowGroupBox;
  ctkWorkflowButtonBoxWidget* ButtonBoxWidget;

  bool ShowButtonBoxWidget;
};

// --------------------------------------------------------------------------
// ctkWorkflowWidgetPrivate methods

//---------------------------------------------------------------------------
ctkWorkflowWidgetPrivate::ctkWorkflowWidgetPrivate()
{
  this->WorkflowGroupBox = 0;
  this->ButtonBoxWidget = 0;

  this->ShowButtonBoxWidget = true;
}

//---------------------------------------------------------------------------
ctkWorkflowWidgetPrivate::~ctkWorkflowWidgetPrivate()
{
  if (!this->Workflow.isNull())
    {
    foreach(ctkWorkflowStep* step, this->Workflow.data()->steps())
      {
      ctkWorkflowWidgetStep * widgetStep = dynamic_cast<ctkWorkflowWidgetStep*>(step);
      if (widgetStep)
        {
        widgetStep->setVisible(false);
        widgetStep->setParent(0);
        }
      }
    }
}

// --------------------------------------------------------------------------
// ctkWorkflowWidgetMethods

// --------------------------------------------------------------------------
ctkWorkflowWidget::ctkWorkflowWidget(QWidget* _parent) : Superclass(_parent)
  , d_ptr(new ctkWorkflowWidgetPrivate)
{
  Q_D(ctkWorkflowWidget);
  d->WorkflowGroupBox = new ctkWorkflowGroupBox(this);
  d->ButtonBoxWidget = new ctkWorkflowButtonBoxWidget();
}

// --------------------------------------------------------------------------
ctkWorkflowWidget::~ctkWorkflowWidget()
{
}

// --------------------------------------------------------------------------
ctkWorkflow* ctkWorkflowWidget::workflow()const
{
  Q_D(const ctkWorkflowWidget);
  return d->Workflow.data();
}

// --------------------------------------------------------------------------
CTK_GET_CPP(ctkWorkflowWidget, ctkWorkflowGroupBox*, workflowGroupBox, WorkflowGroupBox);
CTK_GET_CPP(ctkWorkflowWidget, bool, showButtonBoxWidget, ShowButtonBoxWidget);
CTK_SET_CPP(ctkWorkflowWidget, bool, setShowButtonBoxWidget, ShowButtonBoxWidget);
CTK_GET_CPP(ctkWorkflowWidget, ctkWorkflowButtonBoxWidget*, buttonBoxWidget, ButtonBoxWidget);

// --------------------------------------------------------------------------
void ctkWorkflowWidget::setWorkflow(ctkWorkflow* newWorkflow)
{
  Q_D(ctkWorkflowWidget);

  if (!newWorkflow)
    {
    logger.error(QString("setWorkflow - cannot set workflow to NULL"));
    return;
    }

  if (!d->Workflow.isNull())
    {
    QObject::disconnect(d->Workflow.data(), SIGNAL(currentStepChanged(ctkWorkflowStep*)),
                        this, SLOT(onCurrentStepChanged(ctkWorkflowStep)));
    QObject::disconnect(d->Workflow.data(), SIGNAL(stepRegistered(ctkWorkflowStep*)),
                        this, SLOT(onStepRegistered(ctkWorkflowStep)));
    }

  d->Workflow = QWeakPointer<ctkWorkflow>(newWorkflow);

  if (!d->Workflow.isNull())
    {
    foreach(ctkWorkflowStep* step, d->Workflow.data()->steps())
      {
      this->onStepRegistered(step);
      }
    }

  QObject::connect(newWorkflow, SIGNAL(currentStepChanged(ctkWorkflowStep*)), this, SLOT(onCurrentStepChanged(ctkWorkflowStep*)));
  QObject::connect(newWorkflow, SIGNAL(stepRegistered(ctkWorkflowStep*)), this, SLOT(onStepRegistered(ctkWorkflowStep*)));

  d->ButtonBoxWidget->setWorkflow(newWorkflow);
}

// --------------------------------------------------------------------------
void ctkWorkflowWidget::onCurrentStepChanged(ctkWorkflowStep* currentStep)
{
  if (currentStep)
    {
    this->updateStepUI(currentStep);
    this->updateButtonBoxUI(currentStep);
    }
}

// --------------------------------------------------------------------------
void ctkWorkflowWidget::onStepRegistered(ctkWorkflowStep* step)
{
  if (step->isWidgetType())
    {
    QWidget * widget = dynamic_cast<QWidget*>(step);
    Q_ASSERT(widget);
    widget->setParent(this);
    widget->setVisible(false);
    }
}

// --------------------------------------------------------------------------
void ctkWorkflowWidget::updateStepUI(ctkWorkflowStep* currentStep)
{
  Q_D(ctkWorkflowWidget);
  Q_ASSERT(currentStep);
  Q_ASSERT(d->WorkflowGroupBox);

  // Create layout and WorkflowGroupBox if this is our first time here
  if (!this->layout())
    {
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->addWidget(d->WorkflowGroupBox);

    if (d->ShowButtonBoxWidget)
      {
      layout->addWidget(d->ButtonBoxWidget);
      }

    layout->setContentsMargins(0,0,0,0);
    }

  d->WorkflowGroupBox->updateGroupBox(currentStep);
}

// --------------------------------------------------------------------------
void ctkWorkflowWidget::updateButtonBoxUI(ctkWorkflowStep* currentStep)
{
  Q_D(ctkWorkflowWidget);
  Q_ASSERT(currentStep);

  // Update the button box widget if we want to show it
  if (d->ShowButtonBoxWidget)
    {
    d->ButtonBoxWidget->updateButtons(currentStep);
    }
}
