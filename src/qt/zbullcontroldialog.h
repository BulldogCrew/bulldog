// Copyright (c) 2017-2019 The bulldog developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef zbullCONTROLDIALOG_H
#define zbullCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zbull/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class zbullControlDialog;
}

class CzbullControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CzbullControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CzbullControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CzbullControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class zbullControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit zbullControlDialog(QWidget *parent);
    ~zbullControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::zbullControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CzbullControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // zbullCONTROLDIALOG_H
