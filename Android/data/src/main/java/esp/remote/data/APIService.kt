package esp.remote.data

import esp.remote.domain.models.CounterModel
import esp.remote.domain.models.IdsModel
import esp.remote.domain.models.NeuronModel
import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.Path
import retrofit2.http.Query

interface APIService {
    @POST("/oins/{id}/key{key}")
    fun loadKeys(
            @Path("id") id: Int,
            @Path("key") key: Int,
            @Query("keyValue") keyValue: Int
    ): Call<NeuronModel>

    @POST("/oins/{id}/res{res}")
    fun loadRes(
            @Path("id") id: Int,
            @Path("res") res: Int,
            @Query("resValue") resValue: Int
    ): Call<NeuronModel>

    @GET("count")
    fun loadCount(): Call<CounterModel>

    @GET("ids")
    fun loadIds(): Call<IdsModel>

    @GET("/oins/{id}")
    fun loadValues(@Path("id") id: Int): Call<NeuronModel>
}