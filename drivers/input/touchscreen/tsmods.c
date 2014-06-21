#include "tsmods.h"
#include <linux/kobject.h>
#include <linux/sysfs.h>

int readval,s2w_activate,l2w_activate,f2w_activate;

static ssize_t TSMODS_status_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
return sprintf(buf, "%d\n", readval);
}

static ssize_t TSMODS_status_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

int change_val;

sscanf(buf, "%du", &change_val);
readval=change_val;
s2w_activate=readval/100; //x00
l2w_activate= (readval/10)%10;//0x0
f2w_activate=readval%10;//00x
return count;
}

static struct kobj_attribute TSMODS_status_attribute =
__ATTR(readval, 0666, TSMODS_status_show, TSMODS_status_store);

static struct attribute *TSMODS_status_attrs[] = {
&TSMODS_status_attribute.attr,
NULL,
};

static struct attribute_group TSMODS_status_attr_group = {
.attrs = TSMODS_status_attrs,
};

static struct kobject *TSMODS_status_kobj;



int TSMODS_init(void)
{
  int retval;

  readval = 000; 

  TSMODS_status_kobj = kobject_create_and_add("TSMODS", kernel_kobj);
  if (!TSMODS_status_kobj) {
      return -ENOMEM;
  }

  retval = sysfs_create_group(TSMODS_status_kobj, &TSMODS_status_attr_group);

  if (retval)
    kobject_put(TSMODS_status_kobj);

  if (retval)
    kobject_put(TSMODS_status_kobj);

  return (retval);
}

void TSMODS_exit(void)
{
  kobject_put(TSMODS_status_kobj);
}

module_init(TSMODS_init);
module_exit(TSMODS_exit);
