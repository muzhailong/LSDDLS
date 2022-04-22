//
// Generated file, do not edit! Created by nedtool 5.0 from SimPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "SimPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("SimPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("SimPacketType"));
    e->insert(ECSSIM_CONN_REQ, "ECSSIM_CONN_REQ");
    e->insert(ECSSIM_CONN_ACK, "ECSSIM_CONN_ACK");
    e->insert(ECSSIM_DISC_REQ, "ECSSIM_DISC_REQ");
    e->insert(ECSSIM_DISC_ACK, "ECSSIM_DISC_ACK");
    e->insert(ECSSIM_DATA_W, "ECSSIM_DATA_W");
    e->insert(ECSSIM_DATA_A, "ECSSIM_DATA_A");
    e->insert(ECSSIM_DATA_BACKFORWARD_G, "ECSSIM_DATA_BACKFORWARD_G");
    e->insert(ECSSIM_DATA_ALLREDUCE_G, "ECSSIM_DATA_ALLREDUCE_G");
    e->insert(ECSSIM_CONFIG, "ECSSIM_CONFIG");
    e->insert(ECSSIM_BUSY, "ECSSIM_BUSY");
    e->insert(ECSSIM_SYNC_REQ, "ECSSIM_SYNC_REQ");
    e->insert(ECSSIM_SYNC_ACK, "ECSSIM_SYNC_ACK");
    e->insert(ECSSIM_OP_FINISHED, "ECSSIM_OP_FINISHED");
    e->insert(ECSSIM_START_MICRO_BATCH, "ECSSIM_START_MICRO_BATCH");
    e->insert(ECSSIM_FORWARD_OP_FINISHED, "ECSSIM_FORWARD_OP_FINISHED");
    e->insert(ECSSIM_BACKWARD_OP_FINISHED, "ECSSIM_BACKWARD_OP_FINISHED");
    e->insert(FORWARD_STARTED, "FORWARD_STARTED");
    e->insert(FORWARD_FINISHED, "FORWARD_FINISHED");
    e->insert(BACKWARD_STARTED, "BACKWARD_STARTED");
    e->insert(BACKWARD_FINISHED, "BACKWARD_FINISHED");
    e->insert(BACKWARD_OP_FINISHED, "BACKWARD_OP_FINISHED");
    e->insert(ALLREDUCE_STARTED, "ALLREDUCE_STARTED");
    e->insert(ALLREDUCE_FINISHED, "ALLREDUCE_FINISHED");
    e->insert(ALLREDUCE_RUNNING, "ALLREDUCE_RUNNING");
);

Register_Class(SimPacket);

SimPacket::SimPacket(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->srcLocalRank = 0;
    this->srcRank = 0;
    this->destLocalRank = 0;
    this->destRank = 0;
    this->opId = 0;
}

SimPacket::SimPacket(const SimPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

SimPacket::~SimPacket()
{
}

SimPacket& SimPacket::operator=(const SimPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void SimPacket::copy(const SimPacket& other)
{
    this->srcLocalRank = other.srcLocalRank;
    this->srcRank = other.srcRank;
    this->destLocalRank = other.destLocalRank;
    this->destRank = other.destRank;
    this->opId = other.opId;
}

void SimPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->srcLocalRank);
    doParsimPacking(b,this->srcRank);
    doParsimPacking(b,this->destLocalRank);
    doParsimPacking(b,this->destRank);
    doParsimPacking(b,this->opId);
}

void SimPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->srcLocalRank);
    doParsimUnpacking(b,this->srcRank);
    doParsimUnpacking(b,this->destLocalRank);
    doParsimUnpacking(b,this->destRank);
    doParsimUnpacking(b,this->opId);
}

int SimPacket::getSrcLocalRank() const
{
    return this->srcLocalRank;
}

void SimPacket::setSrcLocalRank(int srcLocalRank)
{
    this->srcLocalRank = srcLocalRank;
}

int SimPacket::getSrcRank() const
{
    return this->srcRank;
}

void SimPacket::setSrcRank(int srcRank)
{
    this->srcRank = srcRank;
}

int SimPacket::getDestLocalRank() const
{
    return this->destLocalRank;
}

void SimPacket::setDestLocalRank(int destLocalRank)
{
    this->destLocalRank = destLocalRank;
}

int SimPacket::getDestRank() const
{
    return this->destRank;
}

void SimPacket::setDestRank(int destRank)
{
    this->destRank = destRank;
}

int SimPacket::getOpId() const
{
    return this->opId;
}

void SimPacket::setOpId(int opId)
{
    this->opId = opId;
}

class SimPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SimPacketDescriptor();
    virtual ~SimPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(SimPacketDescriptor);

SimPacketDescriptor::SimPacketDescriptor() : omnetpp::cClassDescriptor("SimPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

SimPacketDescriptor::~SimPacketDescriptor()
{
    delete[] propertynames;
}

bool SimPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SimPacket *>(obj)!=nullptr;
}

const char **SimPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SimPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SimPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int SimPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *SimPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcLocalRank",
        "srcRank",
        "destLocalRank",
        "destRank",
        "opId",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int SimPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcLocalRank")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcRank")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destLocalRank")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destRank")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "opId")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SimPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **SimPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SimPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SimPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SimPacket *pp = (SimPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SimPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SimPacket *pp = (SimPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrcLocalRank());
        case 1: return long2string(pp->getSrcRank());
        case 2: return long2string(pp->getDestLocalRank());
        case 3: return long2string(pp->getDestRank());
        case 4: return long2string(pp->getOpId());
        default: return "";
    }
}

bool SimPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SimPacket *pp = (SimPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcLocalRank(string2long(value)); return true;
        case 1: pp->setSrcRank(string2long(value)); return true;
        case 2: pp->setDestLocalRank(string2long(value)); return true;
        case 3: pp->setDestRank(string2long(value)); return true;
        case 4: pp->setOpId(string2long(value)); return true;
        default: return false;
    }
}

const char *SimPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *SimPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SimPacket *pp = (SimPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


