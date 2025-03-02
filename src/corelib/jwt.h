/*
 * Copyright (C) 2012-2022 Fanout, Inc.
 *
 * This file is part of Pushpin.
 *
 * $FANOUT_BEGIN_LICENSE:APACHE2$
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $FANOUT_END_LICENSE$
 */

#ifndef JWT_H
#define JWT_H

#include <QByteArray>
#include <QVariant>
#include <QSharedData>
#include <QDir>
#include "rust/jwt.h"

class QString;

namespace Jwt {

enum KeyType {
	Secret = JWT_KEYTYPE_SECRET,
	Ec = JWT_KEYTYPE_EC,
	Rsa = JWT_KEYTYPE_RSA,
};

enum Algorithm
{
	HS256 = JWT_ALGORITHM_HS256,
	ES256 = JWT_ALGORITHM_ES256,
	RS256 = JWT_ALGORITHM_RS256,
};

class EncodingKey
{
public:
	bool isNull() const { return !d; }
	KeyType type() const { if(d) { return d->type; } else { return (KeyType)-1; } }

	const void *raw() const { if(d) { return d->raw; } else { return 0; } }

	static EncodingKey fromSecret(const QByteArray &key);
	static EncodingKey fromPem(const QByteArray &key);
	static EncodingKey fromPemFile(const QString &fileName);
	static EncodingKey fromConfigString(const QString &s, const QDir &baseDir = QDir());

private:
	class Private : public QSharedData
	{
	public:
		KeyType type;
		void *raw;

		Private();
		Private(JwtEncodingKey key);
		~Private();
	};

	QSharedDataPointer<Private> d;
};

class DecodingKey
{
public:
	bool isNull() const { return !d; }
	KeyType type() const { if(d) { return d->type; } else { return (KeyType)-1; } }

	const void *raw() const { if(d) { return d->raw; } else { return 0; } }

	static DecodingKey fromSecret(const QByteArray &key);
	static DecodingKey fromPem(const QByteArray &key);
	static DecodingKey fromPemFile(const QString &fileName);
	static DecodingKey fromConfigString(const QString &s, const QDir &baseDir = QDir());

private:
	class Private : public QSharedData
	{
	public:
		KeyType type;
		void *raw;

		Private();
		Private(JwtDecodingKey key);
		~Private();
	};

	QSharedDataPointer<Private> d;
};

// returns token, null on error
QByteArray encodeWithAlgorithm(Algorithm alg, const QByteArray &claim, const EncodingKey &key);

// returns claim, null on error
QByteArray decodeWithAlgorithm(Algorithm alg, const QByteArray &token, const DecodingKey &key);

QByteArray encode(const QVariant &claim, const EncodingKey &key);
QVariant decode(const QByteArray &token, const DecodingKey &key);

}

#endif
