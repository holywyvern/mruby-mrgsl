/*
 * sprite.c
 *
 *  Created on: 3/1/2015
 *      Author: chronno
 */
#include "mrgsl.h"
#include "tools.h"
#include <mruby.h>
#include <mruby/class.h>

static mrb_value
initialize (mrb_state *mrb, mrb_value self)
{
  mrb_value parent;
  mrb_int count = mrb_get_args (mrb, "|o", &parent);
  if (count == 1)
    {
      mrb_set_iv (mrb, self, "@parent", parent);
      mrgsl_viewport_add_child (parent, self);
    }
  else
    {
      mrb_set_iv (mrb, self, "@parent", mrb_get_gv(mrb, "$viewport"));

      mrgsl_viewport_add_child (mrb_get_gv(mrb, "$viewport"), self);
    }
  mrb_set_iv (mrb, self, "@rect", mrb_new_instance (mrb, "Rect", 0, NULL));
  mrb_set_iv (mrb, self, "@bitmap", mrb_nil_value ());
  mrb_set_iv (mrb, self, "@visible", mrb_true_value ());
  mrb_set_iv (mrb, self, "@x", mrb_fixnum_value (0));
  mrb_set_iv (mrb, self, "@y", mrb_fixnum_value (0));

  return self;
}

void
mruby_mrgsl_sprite_init (mrb_state *mrb)
{
  struct RClass *mrgsl = mrb_module_get (mrb, "MRGSL");
  struct RClass *type = mrb_define_class_under (mrb, mrgsl, "Sprite", mrb->object_class);
  mrb_define_method (mrb, type, "initialize", (mrb_func_t) initialize, MRB_ARGS_OPT(1));
  mrb_attr_accessor (mrb, type, "rect");
  mrb_attr_accessor (mrb, type, "visible");
  mrb_attr_accessor (mrb, type, "parent");
  mrb_attr_accessor (mrb, type, "bitmap");
  mrb_attr_accessor (mrb, type, "x");
  mrb_attr_accessor (mrb, type, "y");
}
