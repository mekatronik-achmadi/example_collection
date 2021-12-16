#ifndef CHIP_H
#define CHIP_H

#include <QMainWindow>
#include "bit_value.h"

#include "chip/m8.h"
#include "chip/m8515.h"

class chip
{
public:
    chip();

public slots:
    QStringList list(void);
    u_int8_t fuse_default(u_int8_t chip_index, u_int8_t fuse_part);
    u_int8_t fuse_restrict(u_int8_t chip_index, u_int8_t fuse_part);
    QStringList fuse_string(u_int8_t chip_index, u_int8_t fuse_part);
    QStringList fuse_tooltip(u_int8_t chip_index, u_int8_t fuse_part);
    QStringList bod_string(u_int8_t chip_index);
    u_int8_t bod_get(u_int8_t chip_index, u_int8_t fuse_part, u_int8_t fuse_input, u_int8_t menu_index);
    u_int8_t bod_set(u_int8_t chip_index, u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input);
    QStringList bootsz_string(u_int8_t chip_index);
    u_int8_t bootsz_get(u_int8_t chip_index, u_int8_t fuse_part, u_int8_t fuse_input, u_int8_t menu_index);
    u_int8_t bootsz_set(u_int8_t chip_index, u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input);
    QStringList osc_string(u_int8_t chip_index);
    u_int8_t osc_get(u_int8_t chip_index, u_int8_t fuse_part, u_int8_t fuse_input, u_int8_t menu_index);
    u_int8_t osc_set(u_int8_t chip_index, u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input);

private:
    m8 v_m8;
    m8515 v_m8515;
};

#endif // CHIP_H
