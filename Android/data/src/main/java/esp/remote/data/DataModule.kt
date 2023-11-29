package esp.remote.data

import dagger.Module
import dagger.Provides

@Module
class DataModule {
    @Provides
    fun provideConnection(address: String) = Connection(address)
}