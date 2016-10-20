#ifndef EDGEMANIPULATOR_H
#define EDGEMANIPULATOR_H

#include <QWidget>
#include "graphtablemodel.h"
#include <memory>
#include <QItemSelectionModel>
namespace Ui {
class EdgeManipulator;
}

class EdgeModifyAction{
public:
    typedef std::shared_ptr<EdgeModifyAction> Ptr;
    EdgeModifyAction(const g2o::EdgeSE3* edge):edge(edge){}
    virtual ~EdgeModifyAction(){}
    virtual void action(g2o::EdgeSE3* pe) = 0;
    const g2o::EdgeSE3* getEdge() const{return edge;}
protected:
    const g2o::EdgeSE3* edge;
};

class EdgeModifyActionChangeInformation:public EdgeModifyAction{
public:
    EdgeModifyActionChangeInformation(const g2o::EdgeSE3* edge, const g2o::EdgeSE3::InformationType& matrix)
        :EdgeModifyAction(edge), info(matrix){        }
    virtual ~EdgeModifyActionChangeInformation(){}
    void action(g2o::EdgeSE3 *pe){
        pe->setInformation(info);
    }
protected:
    g2o::EdgeSE3::InformationType info;
};

typedef QList<EdgeModifyAction::Ptr> EdgeModifications;

class EdgeManipulator : public QWidget
{
    Q_OBJECT
public:
    explicit EdgeManipulator(QWidget *parent = 0);
    ~EdgeManipulator();

Q_SIGNALS:
    void edgesShouldBeRemoved(const QList<const g2o::EdgeSE3*>& edges);
    void edgesShouldBeModified(const EdgeModifications& modifications);

public Q_SLOTS:
    void setEdges(EdgeTableModel* new_table);
    void selectRows(const QList<int>& rows);

private Q_SLOTS:
    //Delete selected edges
    void on_pushButton_Delete_clicked();
    //Change information matrix of selected edges.
    void slot_changeInformationMatrix(const g2o::EdgeSE3::InformationType& new_mat);
    void updateSelections(QItemSelection selected,QItemSelection deselected);
protected:
    EdgeTableModel* edge_table;

private:
    Ui::EdgeManipulator *ui;
};




#endif // EDGEMANIPULATOR_H