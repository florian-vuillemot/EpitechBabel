#ifndef ICONFIG_HH
#define ICONFIG_HH

class IConfig
{
public:
    virtual ~IConfig() {};

    /**
     * Load IConfig file.
     * True for success.
     * @param filename
     * @return
     */
    virtual bool init(std::string const &filename) noexcept = 0;
    /**
     * Find if a config element exist.
     * Return true if exist.
     * @param label
     * @param key
     * @return
     */
    virtual bool exist(std::string const &label, std::string const &key) const noexcept = 0;
    /**
     * Return the element if exist.
     * @param label
     * @param key
     * @return
     * @throw std::out_of_range
     */
    virtual std::string const & get(std::string const &label, std::string const &key) const = 0;
};

#endif // ICONFIG_HH
