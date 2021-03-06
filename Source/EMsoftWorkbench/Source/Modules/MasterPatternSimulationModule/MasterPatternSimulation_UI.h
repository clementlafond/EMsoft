/* ============================================================================
* Copyright (c) 2009-2017 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef _MasterPatternSimulation_UI_h_
#define _MasterPatternSimulation_UI_h_

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"

#include "Modules/IModuleUI.h"
#include "Modules/MasterPatternSimulationModule/MasterPatternSimulationController.h"

#include "ui_MasterPatternSimulation_UI.h"

class QtSSettings;
class QSplashScreen;

class MasterPatternSimulation_UI : public IModuleUI, public Ui::MasterPatternSimulation_UI
{
    Q_OBJECT

  public:
    SIMPL_TYPE_MACRO(MasterPatternSimulation_UI)

    /**
     * @brief MasterPatternSimulation_UI
     * @param parent
     */
    MasterPatternSimulation_UI(QWidget* parent = 0);

    ~MasterPatternSimulation_UI();

    SIMPL_INSTANCE_PROPERTY(MasterPatternSimulationController*, Controller)

    /**
     * @brief readModuleSession
     * @param obj
     */
    void readModuleSession(QJsonObject &obj);

    /**
     * @brief writeModuleSession
     * @param obj
     */
    void writeModuleSession(QJsonObject &obj);

    /**
     * @brief validateData
     */
    bool validateData();

  protected:
    /**
     * @brief setupGui
     */
    void setupGui();

    /**
     * @brief changeEvent
     * @param event
     */
    void changeEvent(QEvent* event);

  protected slots:
    void slot_simulateBtn_clicked();

    void parametersChanged();

  private slots:
    void threadFinished();

  private:
    QString                                                             m_LastFilePath = "";
    QSharedPointer<QFutureWatcher<void>>        m_Watcher;

    /**
     * @brief readCrystalSystemParameters
     * @param obj
     */
    void readComputationalParameters(QJsonObject &obj);

    /**
     * @brief writeCrystalSystemParameters
     * @param obj
     */
    void writeComputationalParameters(QJsonObject &obj);

    /**
     * @brief createValidators
     */
    void createValidators();

    /**
     * @brief createParametersChangedConnections
     */
    void createModificationConnections();

    /**
     * @brief createWidgetConnections
     */
    void createWidgetConnections();

    /**
     * @brief getCreationData
     * @return
     */
    MasterPatternSimulationController::MasterPatternSimulationData getSimulationData();

    MasterPatternSimulation_UI(const MasterPatternSimulation_UI&);    // Copy Constructor Not Implemented
    void operator=(const MasterPatternSimulation_UI&);  // Operator '=' Not Implemented
};

#endif
