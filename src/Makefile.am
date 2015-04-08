DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

SOLARI_CONFIG_INCLUDES=-I$(builddir)/config
SOLARI_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

SOLARI_INCLUDES += -I$(srcdir)/secp256k1/include

LIBSOLARI_SERVER=libsolari_server.a
LIBSOLARI_WALLET=libsolari_wallet.a
LIBSOLARI_COMMON=libsolari_common.a
LIBSOLARI_CLI=libsolari_cli.a
LIBSOLARI_UTIL=libsolari_util.a
LIBSOLARI_CRYPTO=crypto/libsolari_crypto.a
LIBSOLARI_UNIVALUE=univalue/libsolari_univalue.a
LIBSOLARIQT=qt/libsolariqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libsolari_crypto.a \
  libsolari_util.a \
  libsolari_common.a \
  univalue/libsolari_univalue.a \
  libsolari_server.a \
  libsolari_cli.a
if ENABLE_WALLET
SOLARI_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libsolari_wallet.a
endif

if BUILD_SOLARI_LIBS
lib_LTLIBRARIES = libsolariconsensus.la
LIBSOLARI_CONSENSUS=libsolariconsensus.la
else
LIBSOLARI_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_SOLARID
  bin_PROGRAMS += solarid
endif

if BUILD_SOLARI_UTILS
  bin_PROGRAMS += solari-cli solari-tx
endif

.PHONY: FORCE
# solari core #
SOLARI_CORE_H = \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparamsbase.h \
  chainparams.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compressor.h \
  consensus/params.h \
  core_io.h \
  wallet/db.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  pow.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script/interpreter.h \
  script/script_error.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  wallet/crypter.h \
  wallet/walletdb.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libsolari_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between solarid and solari-qt
libsolari_server_a_CPPFLAGS = $(SOLARI_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libsolari_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  $(JSON_H) \
  $(SOLARI_CORE_H)

# wallet: shared between solarid and solari-qt, but only linked
# when wallet enabled
libsolari_wallet_a_CPPFLAGS = $(SOLARI_INCLUDES)
libsolari_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  $(SOLARI_CORE_H)

# crypto primitives library
crypto_libsolari_crypto_a_CPPFLAGS = $(SOLARI_CONFIG_INCLUDES)
crypto_libsolari_crypto_a_SOURCES = \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/sha1.h \
  crypto/ripemd160.h

# univalue JSON library
univalue_libsolari_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp \
  univalue/univalue_escapes.h \
  univalue/univalue.h

# common: shared between solarid, and solari-qt and non-server tools
libsolari_common_a_CPPFLAGS = $(SOLARI_INCLUDES)
libsolari_common_a_SOURCES = \
  arith_uint256.cpp \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  pubkey.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  script/script_error.cpp \
  $(SOLARI_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libsolari_util_a_CPPFLAGS = $(SOLARI_INCLUDES)
libsolari_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(SOLARI_CORE_H)

if GLIBC_BACK_COMPAT
libsolari_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between solari-cli and solari-qt
libsolari_cli_a_CPPFLAGS = $(SOLARI_INCLUDES)
libsolari_cli_a_SOURCES = \
  rpcclient.cpp \
  $(SOLARI_CORE_H)

nodist_libsolari_util_a_SOURCES = $(srcdir)/obj/build.h
#

# solarid binary #
solarid_SOURCES = solarid.cpp
solarid_CPPFLAGS = $(SOLARI_INCLUDES)
solarid_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
solarid_SOURCES += solarid-res.rc
endif

solarid_LDADD = \
  $(LIBSOLARI_SERVER) \
  $(LIBSOLARI_COMMON) \
  $(LIBSOLARI_UNIVALUE) \
  $(LIBSOLARI_UTIL) \
  $(LIBSOLARI_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
solarid_LDADD += libsolari_wallet.a
endif

solarid_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
#

# solari-cli binary #
solari_cli_SOURCES = solari-cli.cpp
solari_cli_CPPFLAGS = $(SOLARI_INCLUDES)
solari_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
solari_cli_SOURCES += solari-cli-res.rc
endif

solari_cli_LDADD = \
  $(LIBSOLARI_CLI) \
  $(LIBSOLARI_UTIL) \
  $(LIBSECP256K1)

solari_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS)
#

# solari-tx binary #
solari_tx_SOURCES = solari-tx.cpp
solari_tx_CPPFLAGS = $(SOLARI_INCLUDES)
solari_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

solari_tx_LDADD = \
  $(LIBSOLARI_UNIVALUE) \
  $(LIBSOLARI_COMMON) \
  $(LIBSOLARI_UTIL) \
  $(LIBSOLARI_CRYPTO) \
  $(LIBSECP256K1)

solari_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# solariconsensus library #
if BUILD_SOLARI_LIBS
include_HEADERS = script/solariconsensus.h
libsolariconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/solariconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libsolariconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libsolariconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libsolariconsensus_la_LIBADD = $(CRYPTO_LIBS)
libsolariconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_SOLARI_INTERNAL

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
