#ifndef DIALOGFILTER_H
#define DIALOGFILTER_H
#include <QGridLayout>
#include "widgets.h"
#include "structures.h"

typedef QList<QFieldsItem*> FieldList;
class DialogFilter : public QDbfDialog
{
    Q_OBJECT
private:
    QGridLayout *laMain;
    QVBoxLayout *laButtons;
    QLabel *lbField;
    QLabel *lbExpression;
    QComboBox *cbField;
    QComboBox *cbExpression;
    QLineEdit *edExpression;
    QDialogButtonBox *buttonBox;
    FieldList fieldsCollection;
    QValidator *validator;

    QString prepare(QFieldsItem *item, QString expression, QString filter);
public:
    explicit DialogFilter(const FieldList fields, const QString &title, QWidget *parent = 0);
    QString getWhere();

private slots:
    void onFieldChange(int index);


};

#endif // DIALOGFILTER_H
