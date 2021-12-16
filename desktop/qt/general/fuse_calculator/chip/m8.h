#ifndef M8_H
#define M8_H

#include <QMainWindow>
#include "bit_value.h"

class m8
{
public:
    m8();

public slots:
    u_int8_t fuse_default(u_int8_t fuse_part);
    u_int8_t fuse_restrict(u_int8_t fuse_part);
    QStringList fuse_string(u_int8_t fuse_part);
    QStringList fuse_tooltip(u_int8_t fuse_part);
    QStringList bod_string(void);
    u_int8_t bod_get(u_int8_t fuse_part, u_int8_t fuse_input, int8_t menu_index);
    u_int8_t bod_set(u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input);
    QStringList bootsz_string(void);
    u_int8_t bootsz_get(u_int8_t fuse_part, u_int8_t fuse_input, int8_t menu_index);
    u_int8_t bootsz_set(u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input);
    QStringList osc_string(void);
    u_int8_t osc_get(u_int8_t fuse_part, u_int8_t fuse_input, int8_t menu_index);
    u_int8_t osc_set(u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input);
};

#endif // M8_H
