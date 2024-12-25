#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/time.h> // для работы со временем



MODULE_AUTHOR("flametoxic");
MODULE_DESCRIPTION("Простой модуль для Томского государственного университета");

static struct proc_dir_entry *tsu_proc_entry;

static int tsu_proc_show(struct seq_file *m, void *v) {
    struct timespec ts;
    struct tm tm_start;
    time_t start_time; // time_t вместо time64_t для совместимости
    time_t current_time; // time_t вместо time64_t для совместимости
    long days;

    // Получаем текущее время
    ktime_get_ts(&ts); // Более безопасный способ получения времени в ядре
    current_time = ts.tv_sec;

    // Определяем дату окончания календаря майя (23 декабря 2012 года, 00:00:00 UTC)
    tm_start.tm_year = 2012 - 1900;
    tm_start.tm_mon = 11;
    tm_start.tm_mday = 23;
    tm_start.tm_hour = 0;
    tm_start.tm_min = 0;
    tm_start.tm_sec = 0;
    tm_start.tm_isdst = 0;

    // Вычисляем количество секунд с начала эпохи для начальной даты (UTC)
    start_time = mktime(&tm_start); // Используем mktime, а не mktime64 для совместимости

    // Вычисляем разницу в днях
    days = (current_time - start_time) / (24 × 60 × 60);

    seq_printf(m, "Дней с окончания календаря майя (23 дек 2012): %ld\n", days);
    return 0;
}

static int tsu_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, tsu_proc_show, NULL);
}

static const struct file_operations tsu_proc_fops = {
    .owner          = THIS_MODULE,
    .open           = tsu_proc_open,
    .read           = seq_read,
    .llseek         = seq_lseek,
    .release        = single_release,
};

static int __init hello_init(void) {
    pr_info("Добро пожаловать в Томский государственный университет\n");
    tsu_proc_entry = proc_create("tsu_lab", 0, NULL, &tsu_proc_fops);
    if (tsu_proc_entry == NULL) {
        pr_err("Ошибка создания /proc/tsu_lab\n");
        return -ENOMEM;
    }
    return 0;
}

static void __exit hello_exit(void) {
    pr_info("Томский государственный университет навсегда!\n");
    remove_proc_entry("tsu_lab", NULL);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");