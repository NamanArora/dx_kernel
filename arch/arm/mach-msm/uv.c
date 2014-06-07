#include "uv.h"
#include <linux/kobject.h>
#include <linux/sysfs.h>

int readval;

static ssize_t uv_status_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
return sprintf(buf, "%d\n", readval);
}

static ssize_t uv_status_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

int change_val;

sscanf(buf, "%du", &change_val);
 readval=change_val;

return count;
}

static struct kobj_attribute uv_status_attribute =
__ATTR(readval, 0666, uv_status_show, uv_status_store);

static struct attribute *uv_status_attrs[] = {
&uv_status_attribute.attr,
NULL,
};

static struct attribute_group uv_status_attr_group = {
.attrs = uv_status_attrs,
};

static struct kobject *uv_status_kobj;



int uV_init(void)
{
  int retval;

  readval = 0; 

  uv_status_kobj = kobject_create_and_add("uV", kernel_kobj);
  if (!uv_status_kobj) {
      return -ENOMEM;
  }

  retval = sysfs_create_group(uv_status_kobj, &uv_status_attr_group);

  if (retval)
    kobject_put(uv_status_kobj);

  if (retval)
    kobject_put(uv_status_kobj);

  return (retval);
}

void uV_exit(void)
{
  kobject_put(uv_status_kobj);
}

module_init(uV_init);
module_exit(uV_exit);
