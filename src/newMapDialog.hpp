/**
 * newMapDialog.hpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#ifndef _NEWMAPDIALOG_HPP
#define _NEWMAPDIALOG_HPP

#include <QSpinBox>
#include <QDialogButtonBox>
#include <QLayout>
#include <QLabel>

#include <QDialog>

class NewMapDialog : public QDialog
{
    Q_OBJECT
    public:
        NewMapDialog(QWidget *parent = 0);
        ~NewMapDialog();

        bool succeeded();
        int width();
        int height();

    private slots:
        void ok_clicked();
        void cancel_clicked();


    private:
        bool success;
        QLabel *widthLabel;
        QLabel *heightLabel;
        QSpinBox *widthSpinBox;
        QSpinBox *heightSpinBox;
        QDialogButtonBox *buttonBox;
        QGridLayout *layout;
};

#endif
