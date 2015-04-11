// Copyright (c) 2011-2014 The Bitcoin Core Developers
// Copyright (c) 2015 Solarminx
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SOLARI_QT_SOLARIADDRESSVALIDATOR_H
#define SOLARI_QT_SOLARIADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class SolariAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SolariAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Solari address widget validator, checks for a valid solari address.
 */
class SolariAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SolariAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // SOLARI_QT_SOLARIADDRESSVALIDATOR_H
