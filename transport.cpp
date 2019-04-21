#include "transport.h"

Transport::Transport(Leapp *parent)
{
	leapp = parent;
}

QString Transport::onKeysExtracted(QStringList keys)
{
	Q_UNUSED(keys);
	return "you done!";
}
